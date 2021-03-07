import org.springframework.jdbc.core.JdbcTemplate;

import java.util.List;

public class OrderDao {

    private final JdbcTemplate jdbcTemplate;
    private OrderDao dao;

    public OrderDao(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public List<Customer> getCustomers() {
        return jdbcTemplate.query("SELECT * FROM customers", new CustomerMapper());
    }

    public void timeControl(){
        jdbcTemplate.execute("DELETE from customers where time < now()");
    }

    public void serveCustomer() {
        jdbcTemplate.update("call last_person_time()");
    }

    public void addCustomer(Customer customer) {
        jdbcTemplate.update("INSERT INTO customers (name,services) VALUES(?, ?);",
                customer.getName(), customer.getSelectedServices());
    }

    public void resetTables(){
        jdbcTemplate.update("DELETE FROM customers");
    }

}
