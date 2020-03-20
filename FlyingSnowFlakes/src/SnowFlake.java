public class SnowFlake {

    private int x;
    private int y;
    private int speed;

    /**
     * 生成雪花的构造函数
     */
    public SnowFlake() {
        // 获取面板宽度
        int width = Configuration.width;
        // 获取面板长度
        int height = Configuration.height;
        // 获取雪花下落最大速度
        int maxFlyingSpeed = Configuration.maxFlyingSpeed;
        // 随机在[0, width]内产生横坐标
        this.x = (int)(Math.random()*(width+1));
        // 随机在[0, height/50]内产生纵坐标
        this.y = (int)(Math.random()*(height/50+1));
        // 随机在[1, maxFlyingSpeed]内产生下落速度
        this.speed = (int)(Math.random()*maxFlyingSpeed+1);
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void fly() {
        this.y += this.speed;
    }

    /**
     * 判断雪花是否落地融化
     * @return
     */
    public boolean isOutOfBoundary() {
        return this.y >= Configuration.height;
    }
}
