package tp1.p3.logic.gameobjects;

import static tp1.p3.view.Messages.status;

import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameItem;
import tp1.p3.logic.GameWorld;

/**
 * Base class for game non playable character in the game.
 *
 */
public abstract class GameObject implements GameItem {

	// ATRIBUTES
	protected GameWorld game;
	protected int col;
	protected int row;
	protected int endurance;
	protected int damage;
	protected int cycles;

	// BUILDERS
	public GameObject() {
	}
	public GameObject(GameWorld game, int col, int row) {
		this.game = game;
		this.col = col;
		this.row = row;
	}

	// METHODS
	// Returns true if a GameObject is in the position (col, row). Otherwise returns false
	public boolean isInPosition(int col, int row) {
		return this.col == col && this.row == row;
	}
	// Returns the column where is a GameObject
	public int getCol() {
		return this.col;
	}
	// Returns the row where is a GameObject
	public int getRow() {
		return this.row;
	}
	// Returns the status of a GameObject to show it in the game/match
	public String toString() {
		if (this.isAlive()) {
			return status(this.getSymbol(), this.getEndurance());
		} else {
			return "";
		}
	}
	@Override
	public boolean fillPosition() {
		return true;
	}
	@Override
	public boolean catchObject() {
		return false;
	}
	// Returns true if a GameObject is alive. Otherwise returns false
	public boolean isAlive() {
		return (this.endurance != 0);
	}
	// Returns the endurance of the GameObject
	public int getEndurance() {
		return this.endurance;
	}
	// Returns the damage of the GameObject
	public int getDamage() {
		return this.damage;
	}
	// Shows the status of a GameObject when enters the game/match
	public void onEnter() {}
	// Shows nothing because the GameObject is not in the game/match
	public void onExit() {}
	// Returns the symbol of a GameObject
	abstract protected String getSymbol();
	// Returns the description of a GameObject
	abstract public String getDescription();
	// Returns the name of a GameObject
	abstract public String getName();
	// Updates the GameObject and its functions
	abstract public void update() throws GameException;
	// Returns the cost of the GameObject
	abstract public int getCost();
}