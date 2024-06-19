package tp1.p2.logic;

import java.util.Random;

import tp1.p2.logic.gameobjects.Sun;

public class SunsManager {

	// CONSTANTS
	private static final int COOLDOWN_RANDOM_SUN = 5;

	// ATRIBUTES
	private GameWorld game;
	private Random rand;
	private int cooldown;
	private int catchedSuns;
	private int generatedSuns;

	// BUILDER
	public SunsManager(GameWorld game, Random rand) {
		this.game = game;
		this.rand = rand;
		this.cooldown = COOLDOWN_RANDOM_SUN;
		this.catchedSuns = 0;
		this.generatedSuns = 0;
	}

	// METHODS
	// Returns the suns catched by user
	public int getCatchedSuns() {
		return this.catchedSuns;
	}
	// Returns the generated suns
	public int getGeneratedSuns() {
		return this.generatedSuns;
	}
	// Updates the cooldown of the generation of suns
	public void update() {
		if (this.cooldown == 0) {
			this.addSun();
			this.cooldown = COOLDOWN_RANDOM_SUN;
		} 
		else {
			this.cooldown--;
		}
	}
	// Returns a random integer
	private int getRandomInt(int bound) {
		return this.rand.nextInt(bound);
	}
	// Adds a sun to the game/match table
	public void addSun() {
		this.generatedSuns++;
		int col = getRandomInt(GameWorld.NUM_COLS);
		int row = getRandomInt(GameWorld.NUM_ROWS);
		game.addItem(new Sun(this.game, col, row), false);
	}
}