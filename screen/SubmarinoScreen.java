import java.awt.Color;
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.Iterator;

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

	private static ArrayList<JLabel> posicoesLixo = new ArrayList<JLabel>();
	private static JFrame frame;
	private static JLabel submarino, txtTotalLixos;
	private static JPanel panel;
	private static Integer totalLixos;

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

		geraLixo();
		initKeyListener();
	}

	public static void drawScreen() {
		panel = new JPanel(null);
		panel.setBackground(new Color(0, 175, 238));

		totalLixos = 0;
		
		ImageIcon submarinoImg = new ImageIcon("assets/submarino.png");
		submarino = new JLabel(submarinoImg);
		txtTotalLixos = new JLabel(totalLixos.toString());
		txtTotalLixos.setForeground(Color.WHITE);

		submarino.setBounds(0, 0, submarinoImg.getIconWidth(), submarinoImg.getIconHeight());
		txtTotalLixos.setBounds(submarino.getLocation().x + 90, submarino.getLocation().y + 23, 50, 20);
		
		panel.add(txtTotalLixos);
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

        txtTotalLixos.setBounds(x + 90, y + 23, 50, 20);
		submarino.setBounds(x, y, dim.width, dim.height);
		verificaLixo(x, y);
	}
	
	public static void geraLixo(){
		Runnable helloRunnable = new Runnable() {
		    public void run() {
		        Random rand = new Random();
				ImageIcon lixoImg = new ImageIcon("assets/lixo.png");
				int x;
				int y;
				JLabel lblTemp = new JLabel(lixoImg);
				
				x = rand.nextInt((SCREEN_WIDTH - 100) / 10) * 10;
				y = rand.nextInt((SCREEN_HEIGHT - 100) / 10) * 10;
				
				lblTemp.setBounds(0, 0, lixoImg.getIconWidth(), lixoImg.getIconHeight());
				lblTemp.setLocation(x, y);
				
				panel.add(lblTemp);
				posicoesLixo.add(lblTemp);
				
				panel.revalidate();
	            panel.repaint();
		    }
		};

		ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);
		executor.scheduleAtFixedRate(helloRunnable, 0, 5, TimeUnit.SECONDS);
	}

	public static void verificaLixo(int x, int y) {
		Iterator<JLabel> i = posicoesLixo.iterator();
		Dimension dim = submarino.getPreferredSize();

		while(i.hasNext()) {
			JLabel lixo = i.next();

			if (lixo.getLocation().x == x && lixo.getLocation().y == y) {
				lixo.setVisible(false);
				i.remove();

				txtTotalLixos.setText((++totalLixos).toString());
			}
		}
	}
}