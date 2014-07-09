/**
 */
package turtle.tests;

import junit.textui.TestRunner;

import turtle.Rotate;
import turtle.TurtleFactory;

/**
 * <!-- begin-user-doc -->
 * A test case for the model object '<em><b>Rotate</b></em>'.
 * <!-- end-user-doc -->
 * @generated
 */
public class RotateTest extends ActionTest {

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static void main(String[] args) {
		TestRunner.run(RotateTest.class);
	}

	/**
	 * Constructs a new Rotate test case with the given name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public RotateTest(String name) {
		super(name);
	}

	/**
	 * Returns the fixture for this Rotate test case.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected Rotate getFixture() {
		return (Rotate)fixture;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see junit.framework.TestCase#setUp()
	 * @generated
	 */
	@Override
	protected void setUp() throws Exception {
		setFixture(TurtleFactory.eINSTANCE.createRotate());
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see junit.framework.TestCase#tearDown()
	 * @generated
	 */
	@Override
	protected void tearDown() throws Exception {
		setFixture(null);
	}

} //RotateTest
