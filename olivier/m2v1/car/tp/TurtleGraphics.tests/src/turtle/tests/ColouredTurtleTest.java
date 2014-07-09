/**
 */
package turtle.tests;

import junit.textui.TestRunner;

import turtle.ColouredTurtle;
import turtle.TurtleFactory;

/**
 * <!-- begin-user-doc -->
 * A test case for the model object '<em><b>Coloured Turtle</b></em>'.
 * <!-- end-user-doc -->
 * @generated
 */
public class ColouredTurtleTest extends TurtleTest {

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static void main(String[] args) {
		TestRunner.run(ColouredTurtleTest.class);
	}

	/**
	 * Constructs a new Coloured Turtle test case with the given name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ColouredTurtleTest(String name) {
		super(name);
	}

	/**
	 * Returns the fixture for this Coloured Turtle test case.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected ColouredTurtle getFixture() {
		return (ColouredTurtle)fixture;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see junit.framework.TestCase#setUp()
	 * @generated
	 */
	@Override
	protected void setUp() throws Exception {
		setFixture(TurtleFactory.eINSTANCE.createColouredTurtle());
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

} //ColouredTurtleTest
