/**
 */
package turtle;

import org.eclipse.emf.cdo.CDOObject;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Stage</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link turtle.Stage#getHeight <em>Height</em>}</li>
 *   <li>{@link turtle.Stage#getWidth <em>Width</em>}</li>
 *   <li>{@link turtle.Stage#getBackgroundColor <em>Background Color</em>}</li>
 *   <li>{@link turtle.Stage#getChoreographies <em>Choreographies</em>}</li>
 *   <li>{@link turtle.Stage#getFarms <em>Farms</em>}</li>
 * </ul>
 * </p>
 *
 * @see turtle.TurtlePackage#getStage()
 * @model
 * @extends CDOObject
 * @generated
 */
public interface Stage extends CDOObject {
	/**
	 * Returns the value of the '<em><b>Height</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Height</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Height</em>' attribute.
	 * @see #setHeight(int)
	 * @see turtle.TurtlePackage#getStage_Height()
	 * @model
	 * @generated
	 */
	int getHeight();

	/**
	 * Sets the value of the '{@link turtle.Stage#getHeight <em>Height</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Height</em>' attribute.
	 * @see #getHeight()
	 * @generated
	 */
	void setHeight(int value);

	/**
	 * Returns the value of the '<em><b>Width</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Width</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Width</em>' attribute.
	 * @see #setWidth(int)
	 * @see turtle.TurtlePackage#getStage_Width()
	 * @model
	 * @generated
	 */
	int getWidth();

	/**
	 * Sets the value of the '{@link turtle.Stage#getWidth <em>Width</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Width</em>' attribute.
	 * @see #getWidth()
	 * @generated
	 */
	void setWidth(int value);

	/**
	 * Returns the value of the '<em><b>Background Color</b></em>' containment reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Background Color</em>' containment reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Background Color</em>' containment reference.
	 * @see #setBackgroundColor(Color)
	 * @see turtle.TurtlePackage#getStage_BackgroundColor()
	 * @model containment="true" required="true"
	 * @generated
	 */
	Color getBackgroundColor();

	/**
	 * Sets the value of the '{@link turtle.Stage#getBackgroundColor <em>Background Color</em>}' containment reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Background Color</em>' containment reference.
	 * @see #getBackgroundColor()
	 * @generated
	 */
	void setBackgroundColor(Color value);

	/**
	 * Returns the value of the '<em><b>Choreographies</b></em>' containment reference list.
	 * The list contents are of type {@link turtle.Choreography}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Choreographies</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Choreographies</em>' containment reference list.
	 * @see turtle.TurtlePackage#getStage_Choreographies()
	 * @model containment="true"
	 * @generated
	 */
	EList<Choreography> getChoreographies();

	/**
	 * Returns the value of the '<em><b>Farms</b></em>' reference list.
	 * The list contents are of type {@link turtle.Farm}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Farms</em>' reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Farms</em>' reference list.
	 * @see turtle.TurtlePackage#getStage_Farms()
	 * @model
	 * @generated
	 */
	EList<Farm> getFarms();

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @model
	 * @generated
	 */
	String display();

} // Stage
