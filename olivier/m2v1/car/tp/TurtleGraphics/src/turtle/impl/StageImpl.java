/**
 */
package turtle.impl;

import java.lang.reflect.InvocationTargetException;

import javax.swing.event.DocumentEvent.ElementChange;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.internal.cdo.CDOObjectImpl;

import turtle.Choreography;
import turtle.Color;
import turtle.Farm;
import turtle.Stage;
import turtle.TurtlePackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Stage</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link turtle.impl.StageImpl#getHeight <em>Height</em>}</li>
 *   <li>{@link turtle.impl.StageImpl#getWidth <em>Width</em>}</li>
 *   <li>{@link turtle.impl.StageImpl#getBackgroundColor <em>Background Color</em>}</li>
 *   <li>{@link turtle.impl.StageImpl#getChoreographies <em>Choreographies</em>}</li>
 *   <li>{@link turtle.impl.StageImpl#getFarms <em>Farms</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class StageImpl extends CDOObjectImpl implements Stage {
	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected StageImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return TurtlePackage.Literals.STAGE;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected int eStaticFeatureCount() {
		return 0;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getHeight() {
		return (Integer)eGet(TurtlePackage.Literals.STAGE__HEIGHT, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setHeight(int newHeight) {
		eSet(TurtlePackage.Literals.STAGE__HEIGHT, newHeight);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getWidth() {
		return (Integer)eGet(TurtlePackage.Literals.STAGE__WIDTH, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setWidth(int newWidth) {
		eSet(TurtlePackage.Literals.STAGE__WIDTH, newWidth);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Color getBackgroundColor() {
		return (Color)eGet(TurtlePackage.Literals.STAGE__BACKGROUND_COLOR, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setBackgroundColor(Color newBackgroundColor) {
		eSet(TurtlePackage.Literals.STAGE__BACKGROUND_COLOR, newBackgroundColor);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	public EList<Choreography> getChoreographies() {
		return (EList<Choreography>)eGet(TurtlePackage.Literals.STAGE__CHOREOGRAPHIES, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@SuppressWarnings("unchecked")
	public EList<Farm> getFarms() {
		return (EList<Farm>)eGet(TurtlePackage.Literals.STAGE__FARMS, true);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated NOT
	 */
	public String display() {
		StringBuilder sb = new StringBuilder();
		EList<Choreography> choreographies = this.getChoreographies();
		for (Choreography choreography : choreographies) {
			sb.append(choreography);
		}
		return sb.toString();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eInvoke(int operationID, EList<?> arguments) throws InvocationTargetException {
		switch (operationID) {
			case TurtlePackage.STAGE___DISPLAY:
				return display();
		}
		return super.eInvoke(operationID, arguments);
	}

} //StageImpl
