package tp1.p3.logic;

import tp1.p3.control.Level;
import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.actions.GameAction;
import tp1.p3.logic.gameobjects.GameObject;

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
	public void addSun() throws GameException;
	// Tries to buy a plant
	public void tryToBuy(int cost) throws GameException;
	// Returns true if it is possible to catch a sun. Otherwise returns false
//	public void tryToCatchObject(int col, int row) throws GameException;
	public boolean tryToCatchObject(int col, int row) throws GameException;
	// Checks the position of a plant and throws an exceptin if it is not valid
	void checkValidPlantPosition(int col, int row) throws GameException;
	// Checks the position of a zombie and throws an exception if it is not valid
	void checkValidZombiePosition(int col, int row) throws GameException;
	// Returns true if it is possible to add a new game item. Otherwise returns false
	public boolean addItem(GameObject item, boolean consumeCoins) throws GameException; // se supone que ya no se declara aquí
	 // Updates if the player wants to quit
    public void playerQuits();
    // Executes the game actions and update the game objects in the board.
    public void update() throws GameException;
    // Returns a copy of the GameItem in the position (col, row)
	public GameItem getGameItemInPosition(int col, int row);
	// Resets the game/match
	public void reset() throws GameException;
	// Reset the game/match with provided parameters
	public void reset(Level level, long seed) throws GameException;
	// Returns the suncoins of the game/match
	public int getSuncoins();
	// Returns true if zombies win the game/match. Otherwise returns false
	public boolean getZombiesArrival();
	// Updates the sunscoins of the game/match by adding 'suncoins' suncoins
	public void addSuncoins(int suncoins);
	// Adds an action to the action list
	public void pushAction(GameAction action);
	// Updates the number of zombies alived in the game/match
	public void setZombiesAlived();
	// Updates the number of suns catched in the game/match
	public void addCatchedSuns();
	// Updates the actual score of the game/match
//	public void setScore(int score);
	// Returns the actual level of the game/match
	public Level getLevel();
	// Returns the actual seed of the game/match
	public long getSeed();
	// Shows the record of the current level
	public void showRecord();
	// Updates the dead zombies
//	public void zombieDied();
}