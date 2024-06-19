package tp1.p2.logic;

public interface GameStatus {
	/*
	 * incluirá todos los métodos que necesita GamePrinter para conocer el estado del mundo
	 * y poder hacer su trabajo*/

	// METHODS
	// Returns the current cycles of the game/match
	public int getCycle();
	// Returns the current suncoins of the game/match
	public int getSuncoins();
	// Returns the GameObjects status if they are in the position (col, row)
	public String positionToString(int col, int row);
	// Updates the current cycles of the game/match
	public void addCycle();
	// Shows the game/match information (cycles, suncoins and remainig zombies)
	public void showInfo();
}