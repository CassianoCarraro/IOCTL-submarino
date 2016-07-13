import java.awt.Color;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Dimension;

public class SubmarinoScreen {
	private static final int UP = 65;
	private static final int LEFT = 68;
	private static final int DOWN = 66;
	private static final int RIGHT = 67;
	private static final int MOV_SIZE = 10;
	private static final int SCREEN_WIDTH = 800;
	private static final int SCREEN_HEIGHT = 600;

	private static JFrame frame;
	private static JLabel submarino;

	private static native int keyListner();
	
	static {
		System.loadLibrary("subscreen");
	}

	public static void main(String[] args) {
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		frame.setTitle("Trabalho de Fundamentos de SO");

		drawScreen();

		frame.setVisible(true);

		initKeyListener();
	}

	public static void drawScreen() {
		JPanel panel = new JPanel(null);
		panel.setBackground(new Color(0, 175, 238));

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
		int x = submarino.getLocation().x;
		int y = submarino.getLocation().y;

		Dimension dim = submarino.getPreferredSize();

		if (key == UP && y > 0) {
    		y = y - MOV_SIZE;
    	} else if (key == DOWN && y < (SCREEN_HEIGHT - dim.height * 2)) {
    		y = y + MOV_SIZE;
        } else if (key == LEFT && x > 0 ) {
    		x = x - MOV_SIZE;
        } else if (key == RIGHT && x < (SCREEN_WIDTH - dim.width)) {
    		x = x + MOV_SIZE;
        }

		
		submarino.setBounds(x, y, dim.width, dim.height);
	}
}