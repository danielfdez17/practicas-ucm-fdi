package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;

// creo que será la clase padre de TODOS los zombies que tendremos que implementar a partir de la parte 2 de la Pr2
// creo que es para poner nosotros los zombies en el juego
public class ZombieFactory {
	
	// ATRIBUTES
	private static GameWorld game;
	private static int col, row;
	
	// METHODS
	// Returns a copy of the zombie if it is valid. Otherwise returns null
	public static Zombie spawnZombie(GameWorld game, int col, int row) {
		Zombie z = null;
		//if (isValidZombie(zombieName))
		return z;
	}
	// Returns the available type of zombies are in the game/match
	public static Object getAvailableZombies() {
		// TODO Auto-generated method stub
		return null;
	}
	// Returns the list size of the available type of zombies in the game/match 
	public int size() {
		// TODO Auto-generated method stub
		return 1;
	}

}