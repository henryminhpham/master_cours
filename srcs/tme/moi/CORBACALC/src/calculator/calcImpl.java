package calculator;

import calculator.serv_calcPackage.ZeroDiv;

public class calcImpl implements serv_calcOperations{
	
	int test=0;

	@Override
	public int add(int val1, int val2) {
		// TODO Auto-generated method stub
		this.test++;
		System.out.println(this.test);
		return val1+val2;
	}

	@Override
	public int sub(int val1, int val2) {
		// TODO Auto-generated method stub
		return val1 - val2;
	}

	@Override
	public int mult(int val1, int val2) {
		// TODO Auto-generated method stub
		return val1 * val2;
	}

	@Override
	public int div(int val1, int val2) throws ZeroDiv {
		// TODO Auto-generated method stub
		if (val2 == 0){
			ZeroDiv e = new ZeroDiv("probleme");
			throw e;
		}
		else
			return val1/val2;
	}
}
