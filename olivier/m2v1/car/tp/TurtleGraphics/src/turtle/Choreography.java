/**
 */
package turtle;

import org.eclipse.emf.cdo.CDOObject;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Choreography</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link turtle.Choreography#getSequence <em>Sequence</em>}</li>
 * </ul>
 * </p>
 *
 * @see turtle.TurtlePackage#getChoreography()
 * @model
 * @extends CDOObject
 * @generated
 */
public interface Choreography extends CDOObject {
	/**
	 * Returns the value of the '<em><b>Sequence</b></em>' containment reference list.
	 * The list contents are of type {@link turtle.Action}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Sequence</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Sequence</em>' containment reference list.
	 * @see turtle.TurtlePackage#getChoreography_Sequence()
	 * @model containment="true"
	 * @generated
	 */
	EList<Action> getSequence();

} // Choreography
