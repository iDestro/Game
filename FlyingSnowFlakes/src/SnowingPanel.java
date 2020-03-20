import java.awt.*;
import java.util.*;
import java.util.concurrent.CopyOnWriteArrayList;

public class SnowingPanel extends Panel implements Runnable{

    // 用于存放雪花的线程安全的集合
    private CopyOnWriteArrayList<SnowFlake> snowFlakes = new CopyOnWriteArrayList<>();

    /**
     * 用于初始化雪花的构造函数
     * @param snowFlakeNum:将要产生雪花的数量
     */
    public SnowingPanel(int snowFlakeNum) {
        generateSnowFlakes(snowFlakeNum);
	}

    /**
     * 用于产生雪花的函数
     * @param snowFlakeNum:将要产生雪花的数量
     */
	public void generateSnowFlakes(int snowFlakeNum) {
        for (int i = 0; i < snowFlakeNum; i++) {
            this.snowFlakes.add(new SnowFlake());
        }
    }

    /**
     * 重生落地融化的雪花
     * @param addSnowFlakesNum:需要重生的数量，即落地的雪花数
     */
    public void reGenerateSnowFlakes(int addSnowFlakesNum) {
        for (int i = 0; i < addSnowFlakesNum; i++) {
            this.snowFlakes.add(new SnowFlake());
        }
    }

    /**
     * 将融化的雪花丢弃（即落地的雪花）
     * @param invalidSnowFlakes:用于存储融化的雪花
     */
    public void removeInvalidSnowFlakes(LinkedList<SnowFlake> invalidSnowFlakes) {
        for (SnowFlake snowFlake:invalidSnowFlakes) {
            this.snowFlakes.remove(snowFlake);
        }
        reGenerateSnowFlakes(invalidSnowFlakes.size());
        invalidSnowFlakes.clear();
    }

    /**
     * 将雪花们绘制在画板上
     * @param graphics:需要绘制的图形界面
     */
	@Override
	public void paint(Graphics graphics) {
        for (SnowFlake snowFlake:snowFlakes) {
            graphics.drawString("*", snowFlake.getX() , snowFlake.getY());
        }
	}

    /**
     * 控制雪花的飞舞，以及回收融化的雪花
     */
    @Override
    public void run() {

        while (true) {
            // 用于存放落地的雪花
            LinkedList<SnowFlake> invalidSnowFlakes = new LinkedList<>();
            // 控制雪花的飞舞
            for (SnowFlake snowFlake:snowFlakes) {
                snowFlake.fly();
                // 判断雪花是否落地融化
                if (snowFlake.isOutOfBoundary()) {
                    invalidSnowFlakes.add(snowFlake);
                }
            }
            // 丢弃融化的雪花
            removeInvalidSnowFlakes(invalidSnowFlakes);

			try {
				Thread.sleep(30);
			} catch (Exception e) {

			}

			repaint();
		}
    }
}