package tp1.p2.logic;

import static tp1.p2.view.Messages.error;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Random;

import tp1.p2.control.Command;
import tp1.p2.control.ExecutionResult;
import tp1.p2.control.Level;
import tp1.p2.logic.actions.GameAction;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.view.Messages;

public class Game implements GameStatus, GameWorld {
	
	// CONSTANTS
	public static final int INITIAL_SUNCOINS = 50;
	public static final int MAX_SUNS_CATCHED_PER_CYCLE = 1;
	
	// ATRIBUTES
	private Level level;
	private long seed;
	private Random rand;
	private int cycle;
	private boolean playerQuits;
	private int suncoins;
	private int suns_catched_per_cycle;
	private int catched_suns;
	private ZombiesManager zombiesManager;
	private SunsManager sunsManager;
	private GameObjectContainer container;
	private Deque<GameAction> actions;

	// BUILDER
	public Game(long seed, Level level) {
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
		return this.catched_suns;
	}
	@Override
	public void addCycle() {
		this.cycle++;
	}
	// GameWorld METHODS
	@Override
	public boolean isFullyOcuppied(int col, int row) {
		return this.container.isFullyOccupied(col, row);
	}
	@Override
	public void addSun() {
		this.sunsManager.addSun();
	}
	@Override
	public boolean tryToCatchObject(int col, int row) {
		if (this.suns_catched_per_cycle == 1) {
			System.out.println(error(Messages.SUN_ALREADY_CAUGHT));
			return false;			
		}
		else if (this.container.tryToCatchObject(col, row)) {
			this.suns_catched_per_cycle++;
			return true;
		}
		else {
			System.out.println(error(Messages.NO_CATCHABLE_IN_POSITION.formatted(col, row)));
			return false;
		}
		
	}
	@Override
	public boolean addItem(GameObject item, boolean consumeCoins) {
		if (!item.fillPosition()) {
			return this.container.addObject(item);
		}
		else {
			if (!this.container.isFullyOccupied(item.getCol(), item.getRow())) {
				if (this.container.addObject(item)) {
					if (consumeCoins) {
						this.setSuncoins(item.getCost());
					}
					return true;
				}
				else {
					System.out.println(error(Messages.NOT_ENOUGH_COINS));
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
	public void update() {

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
		this.suns_catched_per_cycle = 0;
		// 6. Notify commands that a new cycle started
		Command.newCycle();
	}
	@Override
	public GameItem getGameItemInPosition(int col, int row) {
		return this.container.searchGameObject(col, row);
	}
	@Override
	public void reset() {
		reset(this.level, this.seed);
	}
	/**
	 * Resets the game with the provided level and seed.
	 * 
	 * @param level {@link Level} Used to initialize the game.
	 * @param seed Random seed Used to initialize the game.
	 */
	@Override
	public void reset(Level level, long seed) {
		this.level = level;
		this.seed = seed;
		this.rand = new Random(seed);
		this.cycle = 0;
		this.playerQuits = false;
		this.suncoins = INITIAL_SUNCOINS;
		this.suns_catched_per_cycle = 0;
		this.catched_suns = 0;
		this.actions = new ArrayDeque<>();
		this.zombiesManager = new ZombiesManager(this, this.level, this.rand);
		this.sunsManager = new SunsManager(this, this.rand);
		this.container.EmptyList();
		this.container = new GameObjectContainer(this);
	}
	@Override
	public void setSuncoins(int suncoins) {
		if (this.suncoins >= suncoins) {
			this.suncoins -= suncoins;
		}
	}
	@Override
	public boolean getZombiesArrival() {
		return this.container.getZombiesArrival();
	}
	@Override
	public void addSuncoins(int suncoins) {
		this.catched_suns++;
		this.suncoins += suncoins;
	}
	@Override
	public void pushAction(GameAction gameAction) {
	    this.actions.addLast(gameAction);
	}
	@Override
	public void setZombiesAlived() {
		this.zombiesManager.setZombiesAlived();
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
		return (this.playerWins()|| this.zombiesWin());
	}
	// Returns true if the player wants to quit the game/match. Otherwise returns false
	public boolean isPlayerQuits() {
		return this.playerQuits;
	}
	// Executes the command
	public boolean execute(Command command) {
		ExecutionResult ex;
		boolean execute = false;
		if (command != null) {
			ex = command.execute(this);
			execute = ex.draw();
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
}