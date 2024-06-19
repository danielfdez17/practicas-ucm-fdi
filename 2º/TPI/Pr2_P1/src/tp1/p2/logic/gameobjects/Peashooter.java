package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

// creo que será muy parecido al de la Pr1
// ¿DEBEMOS QUITAR LOS METODOS QUE NO SE USEN Y CAMBIAR LA CLASE A TIPO ABSTRACTA?
public class Peashooter extends Plant {
	
	// CONSTANTS
	public static final int DAMAGE = 1; 
	public static final int COST = 50; 
	public static final int ENDURANCE = 3; 

	// BUILDERS
	public Peashooter() {
		super();
	}
	public Peashooter(GameWorld game, int col, int row) {
		super(game, col, row);
		this.damage = DAMAGE;
		this.cost = COST;
		this.endurance = ENDURANCE;
	}

	// METHODS
	// Shoots a zombie in front of the peashooter if it is found
	private void shoot() {
		int i = this.col + 1;
		boolean found = false;
		GameItem item;
		while ((i < GameWorld.NUM_COLS) && !found) {
			item = game.getGameItemInPosition(i, this.row);
			if (item != null) {
				found = true;
				item.receivePlantAttack(this.damage);
			}
			else {
				i++;
			}
		}
	}
	@Override
	public boolean receiveZombieAttack(int damage) {
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
		return Messages.PEASHOOTER_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.PEASHOOTER_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
//		return Messages.PLANT_DESCRIPTION.formatted(Messages.PEASHOOTER_NAME,COST,DAMAGE,ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.PEASHOOTER_NAME;
	}
	@Override
	public boolean isAlive() {
		return (this.endurance != 0);
	}
	@Override
	public void onEnter() {
//		positionToString(Messages.status(this.getSymbol(), this.getEndurance()));
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
			shoot();
		}
	}
	@Override
	public int getEndurance() {
		return this.endurance;
	}
	@Override
	public int getCost() {
		return this.cost;
	}
	@Override
	public int getDamage() {
		return this.damage;
	}
	@Override // Not used
	public boolean receivePlantAttack(int damage) {
		return false;
	}
}