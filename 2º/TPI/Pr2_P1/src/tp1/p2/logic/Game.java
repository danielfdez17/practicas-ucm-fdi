package tp1.p2.logic;

import java.util.Random;

import tp1.p2.control.Command;

import tp1.p2.control.ExecutionResult;
import tp1.p2.control.Level;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.logic.gameobjects.Plant;
import tp1.p2.logic.gameobjects.PlantFactory;
import tp1.p2.view.Messages;

// implementa los metodos de las interfaces GameStatus y GameWorld
public class Game implements GameStatus, GameWorld {
	
	// CONSTANTS
	public static final int INITIAL_SUNCOINS = 50;
	
	// ATRIBUTES
	private Random rand;
	private Level level;
	private long seed;
	private int cycles;
	private int suncoins;
	private boolean playerQuits;
	private ZombiesManager zombiesManager;
	private GameObjectContainer gameObjects;

	// BUILDER
    public Game(long seed, Level level) {
    	this.rand = new Random(seed);
    	this.level = level;
    	this.seed = seed;
    	this.suncoins = INITIAL_SUNCOINS;
    	this.cycles = 0;
    	this.playerQuits = false;
    	this.zombiesManager = new ZombiesManager(this, this.level, this.rand);
    	this.gameObjects = new GameObjectContainer(this);
	}

    // METHODS
    // Returns true if the zombies or the player win the game/match. Otherwise returns false
	public boolean isFinished() {
		return (ZombiesManager.areAllZombiesDead() || ZombiesManager.arrival());
	}
	// Returns true if the player wants to quit the game/match. Otherwise returns false
	public boolean isPlayerQuits() {
		return this.playerQuits;
	}
	// Executes the command
	public boolean execute(Command command) {
		ExecutionResult ex;
		boolean execute = false;
		// aquí se ejcuta el commando, y devuelve true es posible ejecutarlo y false en caso contrario
		if (command != null) {
			ex = command.execute(this); // ¿qué hacer con el valor devuelto?
			execute = ex.draw();
		}
		return execute;
	}
	// Returns true if the zombies win the game/match. Otherwise retunrs false 
	public boolean zombiesWin() {
		return ZombiesManager.arrival();
	}
	// Returns true if the player wins the game/match. Otrhewise returns false
	public boolean playerWins() {
		return ZombiesManager.areAllZombiesDead();
	}
	// Returns the remaining zombies which have not appear in the game/match yet
	public int getRemainingZombies() {
		return ZombiesManager.getRemainingZombies();
	}
	@Override
	public void showInfo() {
		System.out.println(Messages.NUMBER_OF_CYCLES + " " + this.getCycle());
		System.out.println(Messages.NUMBER_OF_COINS + " " + this.getSuncoins());
		System.out.println(Messages.REMAINING_ZOMBIES + " " + this.getRemainingZombies());	
	}
	@Override
	public void playerQuits() {
		this.playerQuits = true;
	}
	@Override
	public ExecutionResult update() {
		this.addCycle();
		this.gameObjects.Update();
		this.zombiesManager.update();
		return new ExecutionResult(true);
	}
	@Override
	public int getCycle() {
		return this.cycles;
	}
	@Override
	public int getSuncoins() {
		return this.suncoins;
	}
	@Override
	public void addCycle() {
		this.cycles++;
	}
	@Override
	public void addSuncoins(int suncoins) {
		this.suncoins += suncoins;
	}
	@Override
	public void setSuncoins(int suncoins) {
		if (suncoins <= this.suncoins) {
			this.suncoins -= suncoins;
		}
	}
	@Override
	public String positionToString(int col, int row) {
		String string = " ";
		GameObject obj = gameObjects.searchGameObject(col, row);
		if (obj != null) {
			string = obj.toString();
		}
		return string;
	}
	@Override
	public GameItem getGameItemInPosition(int col, int row) {
		return this.gameObjects.searchGameObject(col, row);
	}
	@Override
	public void reset() {
		System.out.println(String.format(Messages.CONFIGURED_LEVEL, level.name()));
		System.out.println(String.format(Messages.CONFIGURED_SEED, seed));
		this.rand = new Random(seed);
    	this.suncoins = INITIAL_SUNCOINS;
    	this.cycles = 0;
    	this.playerQuits = false;
    	this.zombiesManager = new ZombiesManager(this, this.level, this.rand);
    	this.gameObjects.EmptyList();
    	this.gameObjects = new GameObjectContainer(this);
	}
	@Override
	public void reset(Level level, long seed) {
		this.level = level;
		this.seed = seed;
		this.reset();
	}
	@Override
	public boolean addPlant(String plantName, int col, int row) {
		return this.gameObjects.addObject(PlantFactory.spawnPlant(plantName, this, col, row));
	}
	@Override
	public boolean addZombie(GameObject obj) {
		return this.gameObjects.addObject(obj);
	}
}