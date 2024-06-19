package tp1.p1.logic.gameobjects;

import tp1.p1.logic.Game;
import tp1.p1.view.Messages;

public class Peashooter {
	
	// CONSTANTS
	public static final int FREQUENCY = 1; 
	public static final int DAMAGE = 1; 
	public static final int COST = 50; 
	public static final int ENDURANCE = 3; 
	
	// ATRIBUTES
	private int row, col;
	private Game game;
	private int damage;
	private int frequency;
	private int cost;
	private int endurance;
	private boolean is_alive;
	private int cycles;
	// BUILDERS
	// Builder for the peashooter to set the initial game values
	public Peashooter(Game game) {
		this.endurance = ENDURANCE;
		this.damage = DAMAGE;
		this.frequency = FREQUENCY;
		this.cost = COST;
		this.is_alive = true;
		this.game = game;
		this.cycles = 0;
	}

	// METHODS
	// Returns the endurance of the peashooter
	public int getEndurance() {
		return this.endurance;
	}
	// Returns the damage which peashooter cause to zombies
	public int getDamage() {
		return DAMAGE;
	}
	// Returns the frequency when the peashooter shoots (USELESS)
	public int getFrequency() {
		return FREQUENCY;
	}
	// Returns the cost of the peashooter
	public int getCost() {
		return COST;
	}
	// Returs the column where the peashooter is
	public int getCol() {
		return this.col;
	}
	// Returns the row where the peashooter is
	public int getRow() {
		return this.row;
	}
	// Returns the state of the peashooter
	public boolean getIsAlive() {
		return this.is_alive;
	}
	// Returns the cycles that the peashooter is not alive
	public int getCycles() {
		return this.cycles;
	}
	// Updates the cycles since the peashooter is not alive
	public void addCycles() {
		this.cycles++;
	}
	// Updates the endurance of the peashooter
	public void setEndurance(int damage) {
		this.endurance -= damage;
		if (this.endurance < 0) {
			this.endurance = 0;
			this.addCycles();
			this.isAlive();
		}
	}
	// Updates the state of the peashooter
	public void setIsAlive() {
		this.is_alive = isAlive();
	}
	// Updates the col of the peashooter
	public void setCol(int col) {
		this.col = col;
	}
	// Updates the row of the peashooter
	public void setRow(int row) {
		this.row = row;
	}
	// Checks if the peashooter is alive or not
	public boolean isAlive() {
	return !(this.endurance == 0);	
	}
	// Returns true if a zombie gets shot. Returns false in other cases 
	public boolean shootZombie() {
		boolean found = false;
			if (this.isAlive()) {
				int j = this.getCol() + 1;
				while ((j < Game.NUM_COLS) && !found) {
					found = ZombieList.searchZombie(j, this.getRow());
					if (!found) {
						j++;						
					}
				}
				if (found) {
					ZombieList.peashooterDamageZombie(j, this.getRow());
				}
			}
		return found;
	}
	// Returns the description of the peashooter
	public static String getDescription() {
		return Messages.PEASHOOTER_DESCRIPTION.formatted(COST, DAMAGE, ENDURANCE);
	}

}