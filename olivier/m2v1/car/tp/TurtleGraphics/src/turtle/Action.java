/**
 */
package turtle;

import org.eclipse.emf.cdo.CDOObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Action</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link turtle.Action#getTarget <em>Target</em>}</li>
 * </ul>
 * </p>
 *
 * @see turtle.TurtlePackage#getAction()
 * @model abstract="true"
 * @extends CDOObject
 * @generated
 */
public interface Action extends CDOObject {
	/**
	 * Returns the value of the '<em><b>Target</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Target</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Target</em>' reference.
	 * @see #setTarget(Turtle)
	 * @see turtle.TurtlePackage#getAction_Target()
	 * @model required="true"
	 * @generated
	 */
	Turtle getTarget();

	/**
	 * Sets the value of the '{@link turtle.Action#getTarget <em>Target</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Target</em>' reference.
	 * @see #getTarget()
	 * @generated
	 */
	void setTarget(Turtle value);

} // Action
