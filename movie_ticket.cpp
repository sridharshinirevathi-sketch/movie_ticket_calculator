#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    cout << "===================================" << endl;
    cout << "      MOVIE TICKET CALCULATOR" << endl;
    cout << "===================================" << endl;

    cout << "\nAvailable Movies:" << endl;
    cout << "1. Leo" << endl;
    cout << "2. Jailer" << endl;
    cout << "3. Vikram" << endl;

    int movie_choice;
    cout << "Select Movie: ";
    cin >> movie_choice;

    string movie_name;

    if (movie_choice == 1)
    {
        movie_name = "Leo";
    }
    else if (movie_choice == 2)
    {
        movie_name = "Jailer";
    }
    else if (movie_choice == 3)
    {
        movie_name = "Vikram";
    }
    else
    {
        cout << "Invalid Movie Selection" << endl;
        return 0;
    }

    cout << "\nAvailable Show Times:" << endl;
    cout << "1. 10:00 AM" << endl;
    cout << "2. 2:00 PM" << endl;
    cout << "3. 6:00 PM" << endl;
    cout << "4. 10:00 PM" << endl;

    int show_choice;
    cout << "Select Show Time: ";
    cin >> show_choice;

    string show_time;

    if (show_choice == 1)
    {
        show_time = "10:00 AM";
    }
    else if (show_choice == 2)
    {
        show_time = "2:00 PM";
    }
    else if (show_choice == 3)
    {
        show_time = "6:00 PM";
    }
    else if (show_choice == 4)
    {
        show_time = "10:00 PM";
    }
    else
    {
        cout << "Invalid Show Time" << endl;
        return 0;
    }

    int adult_price = 200;
    int child_price = 120;

    cout << "\nTicket Price:" << endl;
    cout << "Adult : Rs.200" << endl;
    cout << "Child : Rs.120" << endl;

    int adult_tickets, child_tickets;

    cout << "\nEnter number of Adult tickets: ";
    cin >> adult_tickets;

    cout << "Enter number of Child tickets: ";
    cin >> child_tickets;

    int adult_amount = adult_tickets * adult_price;
    int child_amount = child_tickets * child_price;

    int ticket_total = adult_amount + child_amount;

    cout << "\n===== SNACKS =====" << endl;
    cout << "1. Popcorn       - Rs.150" << endl;
    cout << "2. Coke          - Rs.100" << endl;
    cout << "3. Popcorn + Coke - Rs.220" << endl;
    cout << "4. No Snacks" << endl;

    int snack_choice;
    cout << "Select Snacks: ";
    cin >> snack_choice;

    string snack_name;
    int snack_price;

    if (snack_choice == 1)
    {
        snack_name = "Popcorn";
        snack_price = 150;
    }
    else if (snack_choice == 2)
    {
        snack_name = "Coke";
        snack_price = 100;
    }
    else if (snack_choice == 3)
    {
        snack_name = "Popcorn + Coke";
        snack_price = 220;
    }
    else if (snack_choice == 4)
    {
        snack_name = "No Snacks";
        snack_price = 0;
    }
    else
    {
        cout << "Invalid Snack Selection" << endl;
        return 0;
    }

    int subtotal = ticket_total + snack_price;

    int discount;

    if (subtotal >= 1000)
    {
        discount = 100;
    }
    else if (subtotal >= 500)
    {
        discount = 50;
    }
    else
    {
        discount = 0;
    }

    double amount_after_discount = subtotal - discount;

    double gst = amount_after_discount * 0.05;

    double final_amount = amount_after_discount + gst;

    cout << "\n===================================" << endl;
    cout << "         BOOKING SUMMARY" << endl;
    cout << "===================================" << endl;

    cout << "Movie Name      : " << movie_name << endl;
    cout << "Show Time       : " << show_time << endl;

    cout << "\nAdult Tickets   : " << adult_tickets << endl;
    cout << "Child Tickets   : " << child_tickets << endl;

    cout << "Ticket Amount   : Rs." << ticket_total << endl;
    cout << "Snacks          : " << snack_name << endl;
    cout << "Snacks Amount   : Rs." << snack_price << endl;

    cout << "-----------------------------------" << endl;

    cout << "Subtotal        : Rs." << subtotal << endl;
    cout << "Discount        : Rs." << discount << endl;

    cout << fixed << setprecision(2);
    cout << "GST (5%)        : Rs." << gst << endl;

    cout << "-----------------------------------" << endl;

    cout << "Final Amount    : Rs." << final_amount << endl;

    cout << "===================================" << endl;
    cout << "       BOOKING SUCCESSFUL!" << endl;
    cout << "===================================" << endl;

    return 0;
}