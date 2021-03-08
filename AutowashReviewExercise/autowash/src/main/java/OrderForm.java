import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

import javax.sql.DataSource;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.TimerTask;
import java.util.Timer;
import java.util.concurrent.*;

public class OrderForm extends JFrame {
    private JPanel mainPanel;
    private JPanel customerPanel;
    private JTextField customerNameTextField;
    private JCheckBox outsideCarWashCheckBox;
    private JCheckBox insideCarWashCheckBox;
    private JCheckBox glassCarWashCheckBox;
    private JButton createOrderButton;
    private JLabel customerNameField;
    private JLabel servicesLabel;
    private JButton exitButton;
    private JLabel currentCustomerLabel;
    private JTable orderTable;
    private OrderDao orderDao;
    private Timer timer = new Timer();
    private ExecutorService service = Executors.newSingleThreadExecutor();

    public OrderForm() {
        orderDao = new OrderDao(jdbcTemplate());
        orderDao.resetTables();
        basicFrameSettings();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                refreshOrderList();
            }
        }, 0, 1000);

        createOrderButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(!customerNameTextField.getText().isEmpty() && sumOfServices()>0){
                    Customer customer = new Customer(customerNameTextField.getText(), sumOfServices());
                    orderDao.addCustomer(customer);
                    service.submit(() -> orderDao.serveCustomer());
                    clearPersonFields();
                    }
                else JOptionPane.showMessageDialog(null, "Проверьте правильность имени и выбранных услуг",
                        "Предупреждение", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                service.shutdown();
                dispatchEvent(new WindowEvent(OrderForm.this, WindowEvent.WINDOW_CLOSING));
            }
        });
    }

    private void clearPersonFields(){
        outsideCarWashCheckBox.setSelected(false);
        insideCarWashCheckBox.setSelected(false);
        glassCarWashCheckBox.setSelected(false);
        customerNameTextField.setText(null);
    }

    private void refreshOrderList(){
        List<Customer> list = new ArrayList(orderDao.getCustomers());
        TableModel table = new CustomerTable(list);
        orderTable.setModel(table);

        if(!list.isEmpty())
            currentCustomerLabel.setText(orderTable.getValueAt(0, 1).toString());
        else currentCustomerLabel.setText("Готов к работе...");
        orderDao.timeControl();
    }

    private int sumOfServices(){
        int count = 0;
        if(outsideCarWashCheckBox.isSelected())
            count+=3;
        if(insideCarWashCheckBox.isSelected())
            count+=2;
        if(glassCarWashCheckBox.isSelected())
            count++;
        return count;
    }

    private DataSource dataSource() {
        DriverManagerDataSource dataSource = new DriverManagerDataSource();

        dataSource.setDriverClassName("org.postgresql.Driver");
        dataSource.setUrl("jdbc:postgresql://localhost:5432/postgres");
        dataSource.setUsername("postgres");
        dataSource.setPassword("postgre");

        return dataSource;
    }

    private JdbcTemplate jdbcTemplate() {
        return new JdbcTemplate(dataSource());
    }

    private Point screenSizeSetting(){
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locationX = (int) ((screenSize.getWidth() - mainPanel.getWidth())/2);
        int locationY = (int) ((screenSize.getHeight() - mainPanel.getHeight())/2);
        Point centerOfScreen = new Point(locationX,locationY);
        return centerOfScreen;
    }

    private void basicFrameSettings() {
        setContentPane(mainPanel);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        pack();
        setLocation(screenSizeSetting());
        setVisible(true);
    }
}
