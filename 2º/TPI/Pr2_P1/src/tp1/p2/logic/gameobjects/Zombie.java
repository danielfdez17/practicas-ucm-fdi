package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameObjectContainer;
import tp1.p2.logic.GameWorld;
import tp1.p2.logic.ZombiesManager;
import tp1.p2.view.Messages;

// creo que será muy parecido al de la Pr1
// ¿DEBEMOS QUITAR LOS METODOS QUE NO SE USEN Y CAMBIAR LA CLASE A TIPO ABSTRACTA?
public class Zombie extends GameObject {
	
	// CONSTANTS
	public static final int ENDURANCE = 5;
	public static final int DAMAGE = 1;
	public static final int SPEED = 1;
	public static final int FREQUENCY = 2;
	
	// ATRIBUTES
	private int cycles;
	
	// BUILDER
	public Zombie(GameWorld game, int col, int row) {
		super(game, col, row);
		this.endurance = ENDURANCE;
		this.damage = DAMAGE;
		this.cycles = 0;
	}
	
	// METHODS
	@Override
	public boolean receivePlantAttack(int damage) {
		boolean recieve = false;
		if (this.endurance > 0) {
			recieve = true;
			this.endurance -= damage;
			if (this.endurance < 0) {
				this.endurance = 0;
			}
		}
		return recieve;
	}
	@Override
	protected String getSymbol() {
		return Messages.ZOMBIE_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.zombieDescription(getSymbol(), SPEED, DAMAGE, ENDURANCE);
//		return Messages.ZOMBIE_DESCRIPTION.formatted(Messages.ZOMBIE_NAME, SPEED, DAMAGE, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.ZOMBIE_NAME;
	}
	@Override
	public boolean isAlive() {
		return (this.endurance != 0);
	}
	@Override
	public void onEnter() {
		System.out.print(Messages.status(this.getSymbol(), this.getEndurance()));
//		System.out.print(Messages.GAME_OBJECT_STATUS.formatted(this.getSymbol(), this.getEndurance()));
	}
	@Override
	public void onExit() {
		System.out.print("");
	}
	@Override
	public void update() {
		if (this.isAlive()) {
			this.cycles++;
			GameItem item = game.getGameItemInPosition(this.col - 1, this.row);
			if (item != null) {  
				item.receiveZombieAttack(this.damage);
			}
			else {
				if (this.cycles > 0 && this.cycles % FREQUENCY == 0) {
					this.col--;	    		
				}
			}
		}
		else {
			ZombiesManager.setZombiesAlived();
		}
	}
	@Override
	public int getEndurance() {
		return this.endurance;
	}
	@Override
	public int getCost() {
		return 0;
	}
	@Override
	public int getDamage() {
		return this.damage;
	}
	@Override // Not used
	public boolean receiveZombieAttack(int damage) {
		return false;
	}
}