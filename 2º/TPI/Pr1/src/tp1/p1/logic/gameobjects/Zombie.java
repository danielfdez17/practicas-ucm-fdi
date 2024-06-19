package tp1.p1.logic.gameobjects;

import tp1.p1.logic.Game;

public class Zombie {
	
	// CONSTANTS
	public static final int ENDURANCE = 5;
	public static final int DAMAGE = 1;
	
	// ATRIBUTES
	private int row, col;
	private int endurance, damage;
	private Game game;
	private boolean is_alive;
	private int cycles;
	
	// BUILDERS
	// Builder for the zombie to set the initial game values
	public Zombie(Game game) {
		this.endurance = ENDURANCE;
		this.damage = DAMAGE;
		this.is_alive = true;
		this.game = game;
		this.cycles = 0;
	}
	
	// METHODS
	// Returns the endurance of the zombie
	public int getEndurance() {
		return this.endurance;
	}
	// Returns the damage that cause the zombie to the plants
	public int getDamage() {
		return this.damage;
	}
	// Returns the column where the zombie is
	public int getCol() {
		return this.col;
	}
	// Returns the row where the zombie is
	public int getRow() {
		return this.row;
	}
	public int getCycles() {
		return this.cycles;
	}
	// Updates the state of the zombie
	public void setEndurance(int damage) {
		this.endurance -= damage;
		if (this.endurance < 0) {
			this.endurance = 0;
			this.isAlive();
		}
	}
	// Updates the col of the zombie
	public void setCol(int col) {
		this.col = col;
	}
	// Updates the row of the zombie
	public void setRow(int row) {
		this.row = row;
	}
	public void addCycles() {
		this.cycles++;
	}
	// Returns the state of the zombie
	public boolean isAlive() {
		return !(this.endurance == 0);
	}
	// Updates the position of the zombie
	public void updatePosition() {
		if (this.getCycles() > 0) {
			if ((this.getCycles() % 2) == 0) {
				this.col--;			
			}			
		}
	}
}