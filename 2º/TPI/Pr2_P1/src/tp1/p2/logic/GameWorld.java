package tp1.p2.logic;

import tp1.p2.control.Command;
import tp1.p2.control.ExecutionResult;
import tp1.p2.control.Level;
import tp1.p2.logic.actions.GameAction;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.logic.gameobjects.Plant;

// Incluirá todos los métodos que necesitan los comandos y objetos del juego
public interface GameWorld {
	
	/*
	 * incluira todos los metodos que necesitan los comandos y los objetos del juego para saber
	 * que pasa en el mundo del juego.
	 * Esta interfaz es privilegiada porque permite poder realizar acciones en el juego*/

	// CONSTANTS
    public static final int NUM_ROWS = 4;
    public static final int NUM_COLS = 8;

    // METHODS
    // Updates if the player wants to quit
    public void playerQuits();
    // Updates the game/match
    public ExecutionResult update();
    // Returns a copy of the GameItem in the position (col, row)
	public GameItem getGameItemInPosition(int col, int row);
	// Returns true if it is possible to add a plant in the position (col, row). Otherwise returns false
	public boolean addPlant(String plantName, int col, int row);
	// Return true if it is possible to add a zombie in the position (col, row). Otherwise returns false
	public boolean addZombie(GameObject obj);
	// Resets the game/match
	public void reset();
	// Reset the game/match with these parameters
	public void reset(Level level, long seed);
	// Returns the current suncoins of the game/match 
	public int getSuncoins();
	// Updates the current suncoins of the game/match if it is possible
	public void addSuncoins(int suncoins);
	// Updates the current suncoins of the game/match if it is possible
	public void setSuncoins(int suncoins);
}