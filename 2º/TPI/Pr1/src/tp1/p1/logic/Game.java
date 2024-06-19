package tp1.p1.logic;

import java.util.Random;

import tp1.p1.control.Level;
import tp1.p1.logic.gameobjects.Peashooter;
import tp1.p1.logic.gameobjects.PeashooterList;
import tp1.p1.logic.gameobjects.Sunflower;
import tp1.p1.logic.gameobjects.SunflowerList;
import tp1.p1.logic.gameobjects.ZombieList;
import tp1.p1.view.Messages;

public class Game {

	// CONSTANTS
	public static final int NUM_ROWS = 4;
	public static final int NUM_COLS = 8;
	
	// ATRIBUTES
	private Random rand;
	private long seed;
	private Level level;
	private int cycles;
	private int suncoins;
	private boolean win, exit;
	private PeashooterList peashooters;
	private SunflowerList sunflowers;
	private ZombieList zombies;
	private ZombiesManager zombiesManager;
	private int remaining_zombies;
	private int cycles_without_zombies;
	
	// BUILDERS
	// Builder for the initial game
	public Game(long seed, Level level) {
		this.rand = new Random(seed);
		this.level = level;
		this.seed = seed;
		this.suncoins = 50;
		this.cycles = 0;
		this.remaining_zombies = level.getNumberOfZombies();
		this.win = false;
		this.exit = false;
		this.peashooters = new PeashooterList();
		this.sunflowers = new SunflowerList();
		this.zombiesManager = new ZombiesManager(this, level, rand);
		this.zombies = new ZombieList(this.remaining_zombies);
		this.cycles_without_zombies = 0;
	}
	
	// METHODS
	// Returns the cycles that has the game
	public int getCycles() {
		return this.cycles;	
	}
	// Returns the suncoins the player has
	public int getSuncoins() {
		return this.suncoins;
	}
	// Returns if the player want to exit the game or not
	public boolean getExit() {
		return this.exit;
	}
	// Returns if the player or the zombies win the game
	public boolean getWin() {
		return this.win;
	}
	// Returns the zombies that did not apear in the game yet
	public int getRemainingZombies() {
		return this.remaining_zombies;
	}
	// Updates the number of cycles of the game
	public void addCycles() {
		this.cycles++;	
	}
	// Updates the suncoins that the player has
	public void addSuncoins(int suncoins) {
		this.suncoins += suncoins;
	}
	// Updates if the player wants to exit the game
	public void exit() {
		this.exit = true;
	}
	// Updates if the player or the zombies win the game
	public void win() {
		this.win = true;
	}
	// Returs the corresponding string of every position in the table
	public String positionToString(int col, int row) {
		String string = " ";
		boolean found = false;
		found = PeashooterList.searchPeashooter(col, row);
		if (found) {
			string = PeashooterList.searchPeashooterICON(col, row);
		}
		else {
			found = SunflowerList.searchSunflower(col, row);
			if (found) {
				string = SunflowerList.searchSunflowerICON(col, row);
			}
			else {
				found = ZombieList.searchZombie(col, row);
				if (found) {
					string = ZombieList.searchZombieICON(col, row);
				}
			}
		}
		return string;
	}
	// Updates the sunflower list
	private void UpdateSunflowerList() {
		this.sunflowers.Update();
	}
	// Updates the peashooter list
	private void UpdatePeashooterList() {
		this.peashooters.Update();
	}
	// Updates the zombie list
	private void UpdateZombieList() {
		this.zombies.Update();
	}
	// Updates the game state
	public void Update() {
//	this.remaining_zombies = ZombiesManager.getRemainingZombies();
	addCycles();
	this.remaining_zombies = ZombiesManager.getRemainingZombies();
	UpdateSunflowerList();
	UpdatePeashooterList();
	UpdateZombieList();
	}
	// Returns true if the player exit the game or player or zombies won the game
	public boolean ended() {
		return (this.Exit() || this.Win());
	}
	// Adds a plant to the game if it is possible
	public void addPlant(String string, int col, int row) {
		boolean add = false;
		if ((string.equals("peashooter") || string.equals("p")) && (this.suncoins >= Peashooter.COST)){
			if ((col < NUM_COLS) && (row < NUM_ROWS)) {
				Peashooter peashooter = new Peashooter(this);
				peashooter.setCol(col);
				peashooter.setRow(row);
				add = PeashooterList.addPeashooter(peashooter);
				if (add) {
					this.suncoins -= Peashooter.COST;					
				}
			}
			else {
				System.out.println(Messages.INVALID_POSITION);
			}
		}
		else if ((string.equals("sunflower") || string.equals("s")) && (this.suncoins >= Sunflower.COST)) {				
			if ((col < NUM_COLS) && (row < NUM_ROWS)) {
				Sunflower sunflower = new Sunflower(this);
				sunflower.setCol(col);
				sunflower.setRow(row);
				add = SunflowerList.addSunflower(sunflower);
				if (add) {
					this.suncoins -= Sunflower.COST;					
				}
			}
			else {
				System.out.println(Messages.INVALID_POSITION);
			}
		}
		else {
			System.out.println(Messages.NOT_ENOUGH_COINS);
		}
	}
	// Resets the game
	public void reset() {
		// TODO Auto-generated method stub
		// borrar todo lo creado y volver a llamar a run() (Controller.java)
		// SOLO FUNCIONA BIEN PARA EL PRIMER CICLO, DESPUÉS SIGUE CON LA PARTIDA ANTERIOR
		this.rand = new Random(this.seed);
		this.cycles = 0;		
		this.exit = false;
		this.win = false;
		this.peashooters = new PeashooterList();
		this.sunflowers = new SunflowerList();
		this.zombies = new ZombieList(level.getNumberOfZombies());
		this.zombiesManager = new ZombiesManager(this, this.level, this.rand);
		this.remaining_zombies = ZombiesManager.getRemainingZombies();
	}
	// Adds a zombie to the game if possible
	public void addZombie() {
		this.zombiesManager.addZombie();
	}
	// Returs true if any zombie arrives their las position
	public boolean zombiesArrival() {
		return this.zombies.ZombiesWin();
	}
	// Returns true if there isn't any more zombies to appear
	public boolean playerWin() {
		return (ZombiesManager.getRemainingZombies() == 0);
	}
	// Returs true if player wants to exit the game
	public boolean Exit() {
		return this.exit;
	}
	// Returns true if any of player or zombies wins the game
	public boolean Win() {
		if (playerWin() && ZombieList.AllZombiesDead()) {
			this.cycles_without_zombies++;
		}
		if ((this.zombiesArrival()) 
				|| (playerWin() && ZombieList.AllZombiesDead() && (this.cycles_without_zombies > 1))) {
			this.win();
		}
		return this.win;
	}
}