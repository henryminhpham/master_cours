import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.Polygon;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.font.FontRenderContext;
import java.awt.font.TextLayout;
import java.awt.geom.AffineTransform;

import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;


public class TP_Java2D implements MouseListener{
	JPanel panGauche;
	JPanel panCenter;
	JRadioButton drawLine;
	JRadioButton fillRect;
	JRadioButton fillPolyGon;
	JRadioButton drawText;
	/**
	 * variables utiles pour dessiner de lignes
	 */
	boolean clicked = false;
	int initX;
	int initY;
	
	public TP_Java2D(){
		JFrame frame = new JFrame("java2D");
				
		panGauche = new JPanel(new GridLayout(0,1));
		panCenter = new JPanel();
		drawLine = new JRadioButton("dessiner ligne");
		fillRect = new JRadioButton("rectangle");
		fillPolyGon = new JRadioButton("fill Polygon");
		drawText = new JRadioButton("affichage de texte");
		ButtonGroup group = new ButtonGroup();
		group.add(drawLine);
		group.add(drawText);group.add(fillPolyGon);
		group.add(fillRect);
		panGauche.add(drawLine);panGauche.add(fillRect);
		panGauche.add(fillPolyGon);
		panGauche.add(drawText);
		frame.add(panGauche,BorderLayout.WEST);
		panCenter.addMouseListener(this);
		frame.add(panCenter,BorderLayout.CENTER);
		//pan.addMouseListener(this);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setPreferredSize(Toolkit.getDefaultToolkit().getScreenSize());
		frame.setVisible(true);
		frame.pack();
		frame.show();
		
	}

	public void mouseClicked(MouseEvent e) {
		
		
		if(drawLine.isSelected()){
			if(clicked == true){
				this.paintLine(panCenter.getGraphics(), initX, initY, e.getX(), e.getY());
				clicked = false;
			}
			else{
				clicked = true;
				initX = e.getX();
				initY = e.getY();
			}
			
			
		}
		if(drawText.isSelected()){
			this.paintText(panCenter.getGraphics(),e.getX(),e.getY());
		}
		if(fillPolyGon.isSelected()){
			paintPolygon(panCenter.getGraphics(),e.getX(),e.getY());
		}
		if(fillRect.isSelected()){
			paintRect(panCenter.getGraphics(),e.getX(),e.getY());
			
		}
		
		
	}

	public void mouseEntered(MouseEvent e) {
		
		
	}

	public void mouseExited(MouseEvent e) {
		
		
	}

	public void mousePressed(MouseEvent e) {
		
	}

	public void mouseReleased(MouseEvent e) {
		
		
	}
	 public void paintText(Graphics g,int x,int y) {
		    Graphics2D g2 =(Graphics2D) g;
		    g2.setColor(Color.red);
		    g2.drawString("Chaîne de caractères simple colorée en rouge",x+50,y+25);
		    Font f1 = new Font("Comic Sans MS",Font.BOLD,22);
		    g2.setFont(f1);
		    g2.setColor(Color.magenta);
		    g2.drawString("Fonte : 22 Comic Sans MS Bold",30+x,55+y);
		  	/**
		  	 * AffineTransform permet de réaliset des rotations, des transalations ...
		  	 */	  
		    AffineTransform at = new AffineTransform();
		    at.setToRotation(0.05);
		    at.setToTranslation(10,0);
		    g2.setTransform(at);
		    g2.setColor(Color.blue);
		    Font f2 = f1.deriveFont(Font.ITALIC|Font.PLAIN);
		    g2.setFont(f2);
		    g2.drawString("Fonte avec une légère rotation",30+x,85+y);
		    //réinitialiser 
		    g2.setTransform(new AffineTransform());
		    FontRenderContext frc = g2.getFontRenderContext();
		    Font f = new Font("Comic Sans MS",Font.BOLD,112);
		    String s = new String("Texte");
		    TextLayout tl = new TextLayout(s,f,frc);
		    Color c1 = new Color(200,0,0) ;
		    Color c2 = new Color(0,0,170) ;
		    //GradientPaint: les formes sont remplies avec un gradient de couleurs, cyclique ou non.
		    GradientPaint gp = new GradientPaint(0,0,c1,40,30,c2,true); 
		    g2.setPaint(gp);
		    tl.draw(g2,30+x,190+y);
		  }

	 public void paintPolygon(Graphics g,int x,int y){
		 Graphics2D g2 =(Graphics2D) g;
		    Polygon p1 = new Polygon();
		    p1.addPoint(x+80,y+40); 
		    p1.addPoint(120+x,40+y); 
		    p1.addPoint(150+x,160+y); 
		    p1.addPoint(180+x,12+y); 
		    p1.addPoint(x,10+y); 
		    g2.fillPolygon(p1);
	 }
	 public void paintLine(Graphics g,int x1,int y1,int x2,int y2){
		 Graphics2D g2 =(Graphics2D) g;
		 g2.drawLine(x1,y1,x2,y2) ;
	 }
	 public void paintRect(Graphics g,int x,int y){
		 Graphics2D g2 =(Graphics2D) g;
		 g2.fillRect(x,y,120,30) ;
	 }
	
	 public static void main (String [] args) 
	  {
	   new TP_Java2D();	   
	  }  
}
