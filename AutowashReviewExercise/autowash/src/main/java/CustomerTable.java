import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.util.List;

public class CustomerTable extends AbstractTableModel {
    private List<Customer> customers;
    private String[] columns = {"Место в очереди","Имя"};


    public CustomerTable(List<Customer> list){
        super();
        customers = list;
    }

    @Override
    public int getRowCount() {
        return customers.size();
    }

    @Override
    public int getColumnCount() {
        return columns.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Customer cust = customers.get(rowIndex);
        switch(columnIndex) {
            case 0:
                return "A"+rowIndex;
            case 1:
                return cust.getName();
            default:
                break;
        }
        return null;
    }

    public String getColumnName(int col) {
        return columns[col] ;
    }
}
