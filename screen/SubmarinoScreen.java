import java.awt.Color;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SubmarinoScreen {
	private static JFrame frame;
	private static JLabel submarino;

	private static native int keyListner();
	
	static {
		System.loadLibrary("subscreen");
	}

	public static void main(String[] args) {
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(800, 600);

		drawScreen();

		frame.setVisible(true);

		initKeyListener();
	}

	public static void drawScreen() {
		JPanel panel = new JPanel(null);
		panel.setBackground(new Color(255, 0, 0));

		ImageIcon submarinoImg = new ImageIcon("assets/submarino.png");
		submarino = new JLabel(submarinoImg);

		submarino.setBounds(0, 0, submarinoImg.getIconWidth(), submarinoImg.getIconHeight());
		panel.add(submarino);

		frame.add(panel);
	}

	public static void initKeyListener() {
		while (true) {
			int key = keyListner();
			if (key != -1) {
			move(key);
			}
		}
	}
	
	public static void move(int key) {
		/*switch (key) {
		case 1:
			
			break;

		default:
			break;
		}*/
		
		System.out.println("Tecla: " + key);
	}
}