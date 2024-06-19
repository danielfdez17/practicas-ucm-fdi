package tp1.p2.logic.actions;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;

public class ExplosionAction implements GameAction {

	// ATRIBUTES
	private int col;
	private int row;
	private int damage;
	private boolean receiveAttack; // if true, plants receiveAttack; if false, zombies receiveAttack

	// BUILDER
	public ExplosionAction(int col, int row, int damage, boolean receiveAttack) {
		this.col = col;
		this.row = row;
		this.damage = damage;
		this.receiveAttack = receiveAttack;
	}

	// GameAction METHOD
	@Override
	public void execute(GameWorld game) {
		for (int i = this.row - 1; i <= this.row + 1; i++) {
			for (int j = this.col - 1; j <= this.col + 1; j++) {
				GameItem item = game.getGameItemInPosition(j, i);
				if (item != null) {
					if (this.receiveAttack) { // plants receive the explosion damage
						item.receiveZombieAttack(this.damage);
					}
					else { // Zombies recieve the explosion damage
						item.receivePlantAttack(this.damage);
					}									
				}
			}
		}
	}
}