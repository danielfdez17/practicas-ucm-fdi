package tp1.p3.logic;

import java.io.File;
import java.io.IOException;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Random;
import java.util.Scanner;

import tp1.p3.logic.Record;
import tp1.p3.control.Command;
import tp1.p3.control.Level;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.control.exceptions.InvalidPositionException;
import tp1.p3.control.exceptions.NotCatchablePositionException;
import tp1.p3.control.exceptions.NotEnoughCoinsException;
import tp1.p3.logic.actions.GameAction;
import tp1.p3.logic.gameobjects.GameObject;
import tp1.p3.view.Messages;

public class Game implements GameStatus, GameWorld {
	
	// CONSTANTS
	public static final int INITIAL_SUNCOINS = 50;
	public static final int MAX_SUNS_CATCHED_PER_CYCLE = 1;
	public static final int ADDED_SUNS = 10;
	
	// ATRIBUTES
	private Level level;
	private long seed;
	private Random rand;
	private int cycle;
	private boolean playerQuits;
	private int suncoins;
	private ZombiesManager zombiesManager;
	private SunsManager sunsManager;
	private GameObjectContainer container;
	private Deque<GameAction> actions;
	private Record record;
	private int deadZombies;

	// BUILDER
	public Game(long seed, Level level) throws GameException {
		this.level = level;
		this.seed = seed;
		this.rand = new Random(seed);
		this.container = new GameObjectContainer(this);
		reset();
	}

	// GameStatus METHODS
	@Override
	public int getCycle() {
		return this.cycle;
	}
	@Override
	public int getSuncoins() {
		return this.suncoins;
	}
	@Override
	public int getRemainingZombies() {
		return this.zombiesManager.getRemainingZombies();
	}
	@Override
	public String positionToString(int col, int row) {
		return this.container.positionToString(col, row);
	}
	@Override
	public int getGeneratedSuns() {
		return this.sunsManager.getGeneratedSuns();
	}
	@Override
	public int getCaughtSuns() {
		return this.sunsManager.getCatchedSuns();
	}
	@Override
	public void addCycle() {
		this.cycle++;
	}
	@Override
	public int getScore() {
		return this.record.getScore();
	}
	// GameWorld METHODS
	@Override
	public boolean isFullyOcuppied(int col, int row) {
		return this.container.isFullyOccupied(col, row);
	}
	@Override
	public void addSun() throws GameException {
		this.sunsManager.addSun();
	}
//	@Override
//	public void tryToCatchObject(int col, int row) throws GameException { // TODO
//		if (!this.container.tryToCatchObject(col, row)) {
//			throw new NotCatchablePositionException(Messages.NO_CATCHABLE_IN_POSITION.formatted(col, row));
//		}
//	}
	@Override
	public boolean tryToCatchObject(int col, int row) throws GameException {
		if (this.container.tryToCatchObject(col, row)) {
			return true;
		}
		else {
			throw new NotCatchablePositionException(Messages.NO_CATCHABLE_IN_POSITION.formatted(col, row));
		}
//		if (this.suns_catched_per_cycle == 1) {
//			System.out.println(error(Messages.SUN_ALREADY_CAUGHT));
//			return false;			
//		}
//		else if (this.container.tryToCatchObject(col, row)) {
//			return true;
//		}
//		else {
//			System.out.println(error(Messages.NO_CATCHABLE_IN_POSITION.formatted(col, row)));
//			return false;
//		}
	}
	@Override
	public boolean addItem(GameObject item, boolean consumeCoins) throws GameException {
		if (!item.fillPosition()) {
			return this.container.addObject(item);
		}
		else {
			if (!this.container.isFullyOccupied(item.getCol(), item.getRow())) {
				if (this.container.addObject(item)) {
					if (consumeCoins) {
						try {
							this.tryToBuy(item.getCost());							
						} catch(GameException e) {
							throw new GameException(e.getMessage());
						}
					}
					return true;
				}
				else {
					throw new NotEnoughCoinsException(Messages.NOT_ENOUGH_COINS);
//					System.out.println(error(Messages.NOT_ENOUGH_COINS));
				}
			}	
		}
		return false;			
	}
	@Override
	public void playerQuits() {
		this.playerQuits = true;
	}
	@Override
	public void update() throws GameException {

		// 1. Execute pending actions
		this.executePendingActions();

		// 2. Execute game Actions
		
		// 3. Game object updates
		this.zombiesManager.update();
		this.sunsManager.update();
		this.container.Update();

		// 4. & 5. Remove dead and execute pending actions
		boolean deadRemoved = true;
		while (deadRemoved || this.areTherePendingActions()) {
			// 4. Remove dead
			deadRemoved = this.container.removeDead();

			// 5. execute pending actions
			this.executePendingActions();
		}
		
		this.addCycle();
		// 6. Notify commands that a new cycle started
		Command.newCycle();
		
		if (this.isFinished() || this.zombiesWin() || this.playerWins()) {
			this.saveScore();
		}
	}
	@Override
	public GameItem getGameItemInPosition(int col, int row) {
		return this.container.searchGameObject(col, row);
	}
	@Override
	public void reset() throws GameException {
		reset(this.level, this.seed);
	}
	/**
	 * Resets the game with the provided level and seed.
	 * 
	 * @param level {@link Level} Used to initialize the game.
	 * @param seed Random seed Used to initialize the game.
	 */
	@Override
	public void reset(Level level, long seed) throws GameException {
		this.level = level;
		this.seed = seed;
		this.rand = new Random(seed);
		this.cycle = 0;
		this.playerQuits = false;
		this.suncoins = INITIAL_SUNCOINS;
		this.actions = new ArrayDeque<>();
		this.zombiesManager = new ZombiesManager(this, this.level, this.rand);
		this.sunsManager = new SunsManager(this, this.rand);
		this.container.EmptyList();
		this.container = new GameObjectContainer(this);
		this.record = new Record();
	}
	@Override
	public boolean getZombiesArrival() {
		return this.container.getZombiesArrival();
	}
	@Override
	public void addSuncoins(int suncoins) {
		this.suncoins += suncoins;
	}
	@Override
	public void pushAction(GameAction gameAction) {
	    this.actions.addLast(gameAction);
	}
	@Override
	public void setZombiesAlived() {
		this.deadZombies++;
		this.zombiesManager.setZombiesAlived();
	}
	@Override
	public void addCatchedSuns() {
		this.addSuncoins(ADDED_SUNS);
		this.sunsManager.addCatchedSuns();
	}
	@Override
	public Level getLevel() {
		return this.level;
	}
	@Override
	public long getSeed() {
		return this.seed;
	}
	@Override
	public void showRecord()  {
		try {
			File f = new File("record.txt");
			try (Scanner scanner = new Scanner(f)) {
				while(scanner.hasNext()) {
					String level_string = scanner.next();
					String level_aux = String.valueOf(this.level);
					if(level_string.equals(level_aux)) {
						String puntos = scanner.next();
						int score_aux =  scanner.nextInt();
						System.out.println(level_aux + " record is " + score_aux);
						}
					}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	// Game METHODS
	// Executes pending actions, if they exists
	private void executePendingActions() {
		while (!this.actions.isEmpty()) {
			GameAction action = this.actions.removeLast();
			action.execute(this);
		}
	}
	// Returns true if there are actions to being executed. Otherwise returns false
	private boolean areTherePendingActions() {
		return this.actions.size() > 0;
	}
    // Returns true if the zombies or the player win the game/match. Otherwise returns false
	public boolean isFinished() {
		return (this.playerWins() || this.zombiesWin());
	}
	// Returns true if the player wants to quit the game/match. Otherwise returns false
	public boolean isPlayerQuits() {
		return this.playerQuits;
	}
	// Executes the command
	public boolean execute(Command command) {
		boolean execute = false;
		if (command != null) {
			try {
				execute = command.execute(this);
			} catch (GameException e) {
				e.printStackTrace();
			}
		}
		return execute;
	}
	// Returns true if the zombies win the game/match. Otherwise retunrs false 
	public boolean zombiesWin() {
		return this.zombiesManager.arrival();
	}
	// Returns true if the player wins the game/match. Otrhewise returns false
	public boolean playerWins() {
		return this.zombiesManager.areAllZombiesDead();
	}
	private void saveScore() {
		this.record.saveScore(this.level);
	}
	@Override
	public void tryToBuy(int cost) throws GameException {
		if (this.getSuncoins() >= cost) {
			this.suncoins -= cost;
		}
		else {
			throw new NotEnoughCoinsException(Messages.NOT_ENOUGH_COINS);
		}
	}
	@Override
	public void checkValidPlantPosition(int col, int row) throws GameException {
		if ((col < 0) || (col >= GameWorld.NUM_COLS) || (row < 0) || (row >= GameWorld.NUM_ROWS)) {
			throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(col, row));
		}
	}
	@Override
	public void checkValidZombiePosition(int col, int row) throws GameException {
		if ((col < 0) || (col > GameWorld.NUM_COLS) || (row < 0) || (row >= GameWorld.NUM_ROWS)) {
			throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(col, row));
		}
	}
}