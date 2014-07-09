/**
 */
package turtle.impl;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EClass;

import turtle.Action;
import turtle.SetPen;
import turtle.TurtlePackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Set Pen</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link turtle.impl.SetPenImpl#isUP <em>UP</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class SetPenImpl extends ActionImpl implements SetPen {
	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected SetPenImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return TurtlePackage.Literals.SET_PEN;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isUP() {
		return (Boolean)eGet(TurtlePackage.Literals.SET_PEN__UP, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setUP(boolean newUP) {
		eSet(TurtlePackage.Literals.SET_PEN__UP, newUP);
	}
	
	/**
	 * @generated NOT
	 */
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("SetPen : ");
		sb.append(isUP()? "UP" : "DOWN");
		sb.append("\nTurtle : ");
		sb.append(this.getTarget());
		sb.append("\n");
		return sb.toString();
	}

} //SetPenImpl
