import java.awt.Color;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SubmarinoScreen {
	private static JFrame frame;
	private static JLabel submarino,lixo;
	private static ArrayList<ArrayList<Integer>> posicoesLixo = new ArrayList<ArrayList<Integer>>();

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
		
		ImageIcon lixoImg = new ImageIcon("assets/lixo.png");
		lixo = new JLabel(lixoImg);
		lixo.setBounds(0, 0, lixoImg.getIconWidth(), lixoImg.getIconHeight());
		
		panel.add(submarino);
		panel.add(lixo);
		geraLixo();
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
	
	public static void geraLixo(){
		Random rand = new Random();
		ArrayList<Integer> posicao = new ArrayList<Integer>();
		int x;
		int y;
		
		x = rand.nextInt(800);
		y = rand.nextInt(600);
		
		posicao.add(x);
		posicao.add(y);
		
		posicoesLixo.add(posicao);
		System.out.println(posicoesLixo);
		lixo.setLocation(x, y);
		
	
	}
}