/**
 */
package turtle.impl;

import org.eclipse.emf.ecore.EClass;

import turtle.Rotate;
import turtle.TurtlePackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Rotate</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link turtle.impl.RotateImpl#getAngle <em>Angle</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class RotateImpl extends ActionImpl implements Rotate {
	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected RotateImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return TurtlePackage.Literals.ROTATE;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public float getAngle() {
		return (Float)eGet(TurtlePackage.Literals.ROTATE__ANGLE, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setAngle(float newAngle) {
		eSet(TurtlePackage.Literals.ROTATE__ANGLE, newAngle);
	}
	
	/**
	 * @generated NOT
	 */
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Rotate : ");
		sb.append(this.getAngle());
		sb.append("\nTurtle : ");
		sb.append(this.getTarget());
		sb.append("\n");
		return sb.toString();
	}

} //RotateImpl
