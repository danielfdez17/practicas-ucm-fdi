package tp1.p3.logic.gameobjects;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import tp1.p3.control.exceptions.GameException;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class ZombieFactory {

	// CONSTANT
	/* @formatter:off */
	private static final List<Zombie> AVAILABLE_ZOMBIES = Arrays.asList(
		new Zombie(),
		new BucketHead(),
		new Sporty(),
		new ExplosiveZombie()
	);
	/* @formatter:on */

	// METHODS
	// Returns true if the 'zombieIdx' matches with an existing zombie. Otherwise returns false
	public static boolean isValidZombie(int zombieIdx) {
		return (zombieIdx >= 0 && zombieIdx < AVAILABLE_ZOMBIES.size());
	}
	// Returns a zombie that matches with 'zombieIdx'. Otherwise returns null
	public static Zombie spawnZombie(int zombieIdx, GameWorld game, int col, int row) throws GameException {
		// va a haber que cambiar la manera de implementar donde comprobar que los gameobjects son válidos
		if (!isValidZombie(zombieIdx)) {
			throw new GameException(Messages.INVALID_GAME_OBJECT);
		}
		else {
			for (Zombie z : AVAILABLE_ZOMBIES) {
				if (z.getIndex() == zombieIdx) {
					return z.spawn(game, col, row);
				}
			}
			return null;
		}			
	}
	// Shows the information of every zombie
	public static void ShowZombiesInfo() {
		for (Zombie z : AVAILABLE_ZOMBIES) {
			System.out.println(z.getDescription());
		}
	}
	public static List<Zombie> getAvailableZombies() {
		return Collections.unmodifiableList(AVAILABLE_ZOMBIES);
	}

	/*
	 * Avoid creating instances of this class
	 */
	private ZombieFactory() {
	}
}