package tp1.p3.control.exceptions;

public class RecordException extends GameException {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6339431812861021114L;
	
	public RecordException(String message) {
		super(message);
	}
	
	public RecordException(Throwable cause) {
		super(cause);
	}

	public RecordException(String message, Throwable cause) {
		super(message, cause);
	}

}
