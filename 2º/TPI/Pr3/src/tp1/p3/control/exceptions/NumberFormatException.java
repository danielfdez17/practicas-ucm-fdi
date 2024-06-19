package tp1.p3.control.exceptions;

public class NumberFormatException extends CommandParseException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 41432280513776779L;

	public NumberFormatException(String message) {
		super(message);
	}
	
	public NumberFormatException(Throwable cause) {
		super(cause);
	}

	public NumberFormatException(String message, Throwable cause) {
		super(message, cause);
	}

}