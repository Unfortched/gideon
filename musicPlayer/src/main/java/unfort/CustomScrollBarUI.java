package unfort;

import javax.swing.*;
import javax.swing.plaf.basic.BasicScrollBarUI;
import java.awt.*;

public class CustomScrollBarUI extends BasicScrollBarUI {
    protected void configureScrollBarColors() {
        trackColor = Color.black;
        setThumbBounds(0, 0, 5, 5);
    }

    @Override
    public Dimension getPreferredSize(JComponent c) {
        c.setPreferredSize(new Dimension(5, 5));
        return super.getPreferredSize(c);
    }

    public void paintTrack(Graphics g, JComponent c, Rectangle trackBounds) {
        Graphics2D g2 = (Graphics2D) g;
        GradientPaint gp = null;

        if (this.scrollbar.getOrientation() == JScrollBar.VERTICAL) {
            gp = new GradientPaint(0, 0, new Color(80, 80, 80),
                    trackBounds.width, 0, new Color(80, 80, 80));
        }

        if (this.scrollbar.getOrientation() == JScrollBar.HORIZONTAL) {
            gp = new GradientPaint(0, 0, new Color(80, 80, 80),
                    trackBounds.height, 0, new Color(80, 80, 80));
        }

        g2.setPaint(gp);
        g2.fillRect(trackBounds.x, trackBounds.y, trackBounds.width, trackBounds.height);
        if (trackHighlight == BasicScrollBarUI.DECREASE_HIGHLIGHT)
            this.paintDecreaseHighlight(g);
        if (trackHighlight == BasicScrollBarUI.INCREASE_HIGHLIGHT)
            this.paintIncreaseHighlight(g);
    }


    @Override
    protected void paintThumb(Graphics g, JComponent c, Rectangle thumbBounds) {
        g.translate(thumbBounds.x, thumbBounds.y);

        Graphics2D g2 = (Graphics2D) g;
        RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
        g2.addRenderingHints(rh);
        g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.5f));
        g2.setPaint(new GradientPaint(c.getWidth() / 2, 1, Color.GRAY, c.getWidth() / 2, c.getHeight(), Color.GRAY));
        g2.fillRoundRect(0, 0, 40, thumbBounds.height, 5, 5);
    }
}
