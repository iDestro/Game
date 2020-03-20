import java.awt.*;
public class Main {

	public static void main(String[] args) {
		Frame w = new Frame();
        SnowingPanel panel = new SnowingPanel(Configuration.snowFlakesNum);
		Thread panel_thread = new Thread(panel);
		panel_thread.start();
		w.add(panel);
		w.setSize(Configuration.width,Configuration.height);
		w.show();
	}
}
