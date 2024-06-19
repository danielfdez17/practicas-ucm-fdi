package tp1.p1.logic.gameobjects;

import tp1.p1.logic.Game;
import tp1.p1.view.Messages;

public class Sunflower {
	
	// CONSTANTS
	public static final int FREQUENCY = 10; 
	public static final int DAMAGE = 0; 
	public static final int COST = 20; 
	public static final int ENDURANCE = 1;
	public static final int SUNCOINS_GENERATED = 10;
	
	// ATRIBUTES
	private int row, col;
	private int damage;
	private int frequency;
	private int cost;
	private int endurance;
	private Game game;
	private boolean is_alive;
	private int cycles;

	// BUILDERS
	// Builder for the sunflower to set the initial game values
	public Sunflower(Game game) {
		this.endurance = ENDURANCE;
		this.damage = DAMAGE;
		this.frequency = FREQUENCY;
		this.cost = COST;
		this.is_alive = true;
		this.game = game;
		this.cycles = -1;
	}
	
	// METHODS
	// Returns the endurance of the sunflower
	public int getEndurance() {
		return this.endurance;
	}
	// Returns the damage of the sunflower
	public int getDamage() {
		return DAMAGE;
	}
	// Return the frequency of the sunflower (USELESS)
	public int getFrequency() {
		return FREQUENCY;
	}
	// Returns the cost of the sunflower
	public int getCost() {
		return COST;
	}
	// Returns the col where the sunflower is
	public int getCol() {
		return this.col;
	}
	// Returns the row where the sunflower is
	public int getRow() {
		return this.row;
	}
	// Returns the cycles since the sunflower has appeared in the game
	public int getCycles() {
		return this.cycles;
	}
	// Updates the endurance of the sunflower
	public void setEndurance(int damage) {
		this.endurance -= damage;
		if (this.endurance < 0) {
			this.endurance = 0;
			this.isAlive();
		}
	}
	// Updates the state of the sunflower
	public void setIsAlive() {
		this.is_alive = this.isAlive();
	}
	// Updates the col of the sunflower
	public void setCol(int col) {
		this.col = col;
	}
	// Updates the row of the sunflower
	public void setRow(int row) {
		this.row = row;
	}
	// Add suncoins every three cycles once the sunflower has appeared in the game
	public void addSuncoins() {
		if (this.getCycles() > 0) {
			if ((this.getCycles() % 3) == 0) {
				this.game.addSuncoins(SUNCOINS_GENERATED);
			}			
		}
	}
	// Updates the cycle that the sundlower generates
	public void addCycles() {
		this.cycles++;
	}
	// Returns the state of the sunflower
	public boolean isAlive() {
		return !(this.endurance == 0);
	}
	// Returns the description of the sunflower
	public static String getDescription() {
		return Messages.SUNFLOWER_DESCRIPTION.formatted(COST, DAMAGE, ENDURANCE);
	}

}