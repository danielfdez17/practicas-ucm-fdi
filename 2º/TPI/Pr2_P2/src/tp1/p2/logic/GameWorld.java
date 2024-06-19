package tp1.p2.logic;

import tp1.p2.control.Level;
import tp1.p2.logic.actions.GameAction;
import tp1.p2.logic.gameobjects.GameObject;

public interface GameWorld {

	// CONSTANTS
	public static final int NUM_ROWS = 4;
	public static final int NUM_COLS = 8;

	// METHODS
	/**
	 * Checks if a cell is fully occupied, that is, the position can be shared between an NPC (Plant, Zombie) and Suns .
	 * 
	 * @param col Column of the cell
	 * @param row Row of the cell
	 * 
	 * @return <code>true</code> if the cell is fully occupied, <code>false</code>
	 *         otherwise.
	 */
	public boolean isFullyOcuppied(int col, int row);
	// Updates the number of suns of the game/match when necessary
	public void addSun();
	// Returns true if it is possible to catch a sun. Otherwise returns false
	public boolean tryToCatchObject(int col, int row);
	// Returns true if it is possible to add a new game item. Otherwise returns false
	public boolean addItem(GameObject item, boolean consumeCoins);
	 // Updates if the player wants to quit
    public void playerQuits();
    // Executes the game actions and update the game objects in the board.
    public void update();
    // Returns a copy of the GameItem in the position (col, row)
	public GameItem getGameItemInPosition(int col, int row);
	// Resets the game/match
	public void reset();
	// Reset the game/match with provided parameters
	public void reset(Level level, long seed);
	// Returns the suncoins of the game/match
	public int getSuncoins();
	// Updates the suncoins of the game/match by substracting 'suncoins' suncoins
	public void setSuncoins(int suncoins);
	// Returns true if zombies win the game/match. Otherwise returns false
	public boolean getZombiesArrival();
	// Updates the sunscoins of the game/match by adding 'suncoins' suncoins
	public void addSuncoins(int suncoins);
	// Adds an action to the action list
	public void pushAction(GameAction action);
	// Updates the number of zombies alived in the game/match
	public void setZombiesAlived();
}