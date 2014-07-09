/**
 */
package turtle;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Coloured Turtle</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link turtle.ColouredTurtle#getColor <em>Color</em>}</li>
 * </ul>
 * </p>
 *
 * @see turtle.TurtlePackage#getColouredTurtle()
 * @model
 * @generated
 */
public interface ColouredTurtle extends Turtle {
	/**
	 * Returns the value of the '<em><b>Color</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Color</em>' containment reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Color</em>' containment reference.
	 * @see #setColor(Color)
	 * @see turtle.TurtlePackage#getColouredTurtle_Color()
	 * @model containment="true" required="true"
	 * @generated
	 */
	Color getColor();

	/**
	 * Sets the value of the '{@link turtle.ColouredTurtle#getColor <em>Color</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Color</em>' containment reference.
	 * @see #getColor()
	 * @generated
	 */
	void setColor(Color value);

} // ColouredTurtle
