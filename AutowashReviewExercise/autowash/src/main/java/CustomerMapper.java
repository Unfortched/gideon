import org.springframework.jdbc.core.RowMapper;

import java.sql.ResultSet;
import java.sql.SQLException;

public class CustomerMapper implements RowMapper<Customer> {

    @Override
    public Customer mapRow(ResultSet resultSet, int i) throws SQLException {
        String customerName = resultSet.getString("name");
        int customerServices = resultSet.getInt("services");
        Customer customer = new Customer(customerName, customerServices);
        return customer;
    }
}
