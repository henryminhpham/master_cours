/**
 */
package turtle;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Rotate</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link turtle.Rotate#getAngle <em>Angle</em>}</li>
 * </ul>
 * </p>
 *
 * @see turtle.TurtlePackage#getRotate()
 * @model
 * @generated
 */
public interface Rotate extends Action {
	/**
	 * Returns the value of the '<em><b>Angle</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Angle</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Angle</em>' attribute.
	 * @see #setAngle(float)
	 * @see turtle.TurtlePackage#getRotate_Angle()
	 * @model
	 * @generated
	 */
	float getAngle();

	/**
	 * Sets the value of the '{@link turtle.Rotate#getAngle <em>Angle</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Angle</em>' attribute.
	 * @see #getAngle()
	 * @generated
	 */
	void setAngle(float value);

} // Rotate
