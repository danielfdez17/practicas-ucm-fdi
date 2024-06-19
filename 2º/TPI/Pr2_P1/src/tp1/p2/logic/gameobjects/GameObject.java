package tp1.p2.logic.gameobjects;

import static tp1.p2.view.Messages.status;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameObjectContainer;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

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
			return Messages.GAME_OBJECT_STATUS.formatted(this.getSymbol(), this.getEndurance());
		} else {
			return "";
		}
	}
	// Updates the endurance of a GameObject
	public void setEndurance(int damage) {
		this.endurance -= damage;
		if (this.endurance < 0) {
			this.endurance = 0;
		}
	}
	// Returns the symbol of a GameObject
	abstract protected String getSymbol();
	// Returns the description of a GameObject
	abstract public String getDescription();
	// Returns the name of a GameObject
	abstract public String getName();
	// Returns true if a GameObject is alive. Otherwise returns false
	abstract public boolean isAlive();
	// Shows the status of a GameObject when enters the game/match
	abstract public void onEnter();
	// Shows nothing because the GameObject is not in the game/match
	abstract public void onExit();
	// Updates the GameObject and its functions
	abstract public void update();
	// Returns the endurance of the GameObject
	abstract public int getEndurance();
	// Returns the cost of the GameObject
	abstract public int getCost();
	// Returns the damage of the GameObject
	abstract public int getDamage();
}