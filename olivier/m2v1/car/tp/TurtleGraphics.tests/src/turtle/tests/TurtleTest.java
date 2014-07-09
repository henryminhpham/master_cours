/**
 */
package turtle.tests;

import junit.framework.TestCase;

import junit.textui.TestRunner;

import turtle.Turtle;
import turtle.TurtleFactory;

/**
 * <!-- begin-user-doc -->
 * A test case for the model object '<em><b>Turtle</b></em>'.
 * <!-- end-user-doc -->
 * @generated
 */
public class TurtleTest extends TestCase {

	/**
	 * The fixture for this Turtle test case.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected Turtle fixture = null;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static void main(String[] args) {
		TestRunner.run(TurtleTest.class);
	}

	/**
	 * Constructs a new Turtle test case with the given name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public TurtleTest(String name) {
		super(name);
	}

	/**
	 * Sets the fixture for this Turtle test case.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void setFixture(Turtle fixture) {
		this.fixture = fixture;
	}

	/**
	 * Returns the fixture for this Turtle test case.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected Turtle getFixture() {
		return fixture;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see junit.framework.TestCase#setUp()
	 * @generated
	 */
	@Override
	protected void setUp() throws Exception {
		setFixture(TurtleFactory.eINSTANCE.createTurtle());
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

} //TurtleTest
