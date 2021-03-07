
public class Customer {
    private int id;
    private String name;
    private int time;
    private int selectedServices;

    public Customer(String name, int services) {
        this.name = name;
        this.selectedServices = services;
    }

    public String getName() {
        return name;
    }

    public int getId() {
        return id;
    }

    public int getSelectedServices() {
        return selectedServices;
    }
}

