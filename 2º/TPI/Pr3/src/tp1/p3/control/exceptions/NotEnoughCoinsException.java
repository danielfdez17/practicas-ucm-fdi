package tp1.p3.control.exceptions;

public class NotEnoughCoinsException extends GameException {

	/**
	 * 
	 */
	private static final long serialVersionUID = -278760529085125457L;
	
	public NotEnoughCoinsException(String message) {
		super(message);
	}
	
	public NotEnoughCoinsException(Throwable cause) {
		super(cause);
	}

	public NotEnoughCoinsException(String message, Throwable cause) {
		super(message, cause);
	}

}
