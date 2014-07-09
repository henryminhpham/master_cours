/**
 */
package turtle;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Set Pen</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link turtle.SetPen#isUP <em>UP</em>}</li>
 * </ul>
 * </p>
 *
 * @see turtle.TurtlePackage#getSetPen()
 * @model
 * @generated
 */
public interface SetPen extends Action {
	/**
	 * Returns the value of the '<em><b>UP</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>UP</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>UP</em>' attribute.
	 * @see #setUP(boolean)
	 * @see turtle.TurtlePackage#getSetPen_UP()
	 * @model
	 * @generated
	 */
	boolean isUP();

	/**
	 * Sets the value of the '{@link turtle.SetPen#isUP <em>UP</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>UP</em>' attribute.
	 * @see #isUP()
	 * @generated
	 */
	void setUP(boolean value);

} // SetPen
