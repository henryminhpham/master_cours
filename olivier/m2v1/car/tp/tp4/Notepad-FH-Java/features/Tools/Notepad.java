import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.undo.*;
import javax.swing.event.*;

class Notepad {

	private JMenu menuTools;
    private JMenuItem menuLanguage;
    
    Notepad() {
    	// ajout du menu
    	Menubar.add(menuTools = new JMenu("Tools"));
    	// 
    	menuTools.add(menuLanguage    = new JMenuItem("Language", new ImageIcon(this.getClass().getResource("images/new.gif"))));
    }
}


