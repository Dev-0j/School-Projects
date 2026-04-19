import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Color;

public class SlideShow extends JFrame {

	//Declare Variables
	private JPanel slidePane;
	private JPanel textPane;
	private JPanel buttonPane;
	private CardLayout card;
	private CardLayout cardText;
	private JButton btnPrev;
	private JButton btnNext;
	private JLabel lblSlide;
	private JLabel lblTextArea;

	/**
	 * Create the application.
	 */
	public SlideShow() throws HeadlessException {
		initComponent();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initComponent() {
		//Initialize variables to empty objects
		card = new CardLayout();
		cardText = new CardLayout();
		slidePane = new JPanel();
		textPane = new JPanel();
		textPane.setBackground(Color.BLUE);
		textPane.setBounds(5, 470, 790, 50);
		textPane.setVisible(true);
		buttonPane = new JPanel();
		btnPrev = new JButton();
		btnNext = new JButton();
		lblSlide = new JLabel();
		lblTextArea = new JLabel();

		//Setup frame attributes
		setSize(800, 600);
		setLocationRelativeTo(null);
		// Updated title to reflect the Product Owner's new requirement
		// to focus on detox and wellness travel destinations
		setTitle("Top 5 Detox/Wellness Travel Destinations");
		getContentPane().setLayout(new BorderLayout(10, 50));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		//Setting the layouts for the panels
		slidePane.setLayout(card);
		textPane.setLayout(cardText);
		
		//logic to add each of the slides and text
		for (int i = 1; i <= 5; i++) {
			lblSlide = new JLabel();
			lblTextArea = new JLabel();
			lblSlide.setText(getResizeIcon(i));
			lblTextArea.setText(getTextDescription(i));
			slidePane.add(lblSlide, "card" + i);
			textPane.add(lblTextArea, "cardText" + i);
		}

		getContentPane().add(slidePane, BorderLayout.CENTER);
		getContentPane().add(textPane, BorderLayout.SOUTH);

		buttonPane.setLayout(new FlowLayout(FlowLayout.CENTER, 20, 10));

		btnPrev.setText("Previous");
		btnPrev.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				goPrevious();
			}
		});
		buttonPane.add(btnPrev);

		btnNext.setText("Next");
		btnNext.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				goNext();
			}
		});
		buttonPane.add(btnNext);

		getContentPane().add(buttonPane, BorderLayout.SOUTH);
	}

	/**
	 * Previous Button Functionality
	 */
	private void goPrevious() {
		card.previous(slidePane);
		cardText.previous(textPane);
	}
	
	/**
	 * Next Button Functionality
	 */
	private void goNext() {
		card.next(slidePane);
		cardText.next(textPane);
	}

	/**
	 * Method to get the images
	 * Updated all image file references to use new detox/wellness
	 * travel images per the Product Owner's revised requirements
	 */
	private String getResizeIcon(int i) {
		String image = ""; 
		if (i==1){
			// Updated: spa resort pool image for wellness destination #1
			image = "<html><body><img width= '800' height='500' src='" + getClass().getResource("/resources/sparesortpool.jpg") + "'</body></html>";
		} else if (i==2){
			// Updated: yoga retreat image for wellness destination #2
			image = "<html><body><img width= '800' height='500' src='" + getClass().getResource("/resources/yogabali.jpg") + "'</body></html>";
		} else if (i==3){
			// Updated: Iceland lagoon image for wellness destination #3
			image = "<html><body><img width= '800' height='500' src='" + getClass().getResource("/resources/bluelagoon4.jpg") + "'</body></html>";
		} else if (i==4){
			// Updated: meditation retreat image for wellness destination #4
			image = "<html><body><img width= '800' height='500' src='" + getClass().getResource("/resources/meditation3.jpg") + "'</body></html>";
		} else if (i==5){
			// Updated: tropical resort image for wellness destination #5
			image = "<html><body><img width= '800' height='500' src='" + getClass().getResource("/resources/tropicalresort.jpg") + "'</body></html>";
		}
		return image;
	}
	
	/**
	 * Method to get the text values
	 * Updated all text descriptions to match the new detox/wellness
	 * travel theme requested by the Product Owner
	 */
	private String getTextDescription(int i) {
		String text = ""; 
		if (i==1){
			// Updated: description for spa resort wellness destination
			text = "<html><body><font size='5'>#1 Spa Resort Retreat.</font> <br>Relax and rejuvenate with luxury spa treatments and thermal pools.</body></html>";
		} else if (i==2){
			// Updated: description for Bali yoga retreat destination
			text = "<html><body><font size='5'>#2 Yoga Retreat in Bali.</font> <br>Find inner peace with guided yoga sessions surrounded by tropical nature.</body></html>";
		} else if (i==3){
			// Updated: description for Iceland Blue Lagoon destination
			text = "<html><body><font size='5'>#3 Blue Lagoon, Iceland.</font> <br>Soak in geothermal hot springs known for their healing mineral waters.</body></html>";
		} else if (i==4){
			// Updated: description for meditation retreat destination
			text = "<html><body><font size='5'>#4 Meditation Retreat.</font> <br>Disconnect from daily stress with guided meditation in a serene setting.</body></html>";
		} else if (i==5){
			// Updated: description for tropical wellness resort destination
			text = "<html><body><font size='5'>#5 Tropical Wellness Resort.</font> <br>Experience holistic wellness programs with ocean views and fresh cuisine.</body></html>";
		}
		return text;
	}
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {

			@Override
			public void run() {
				SlideShow ss = new SlideShow();
				ss.setVisible(true);
			}
		});
	}
}