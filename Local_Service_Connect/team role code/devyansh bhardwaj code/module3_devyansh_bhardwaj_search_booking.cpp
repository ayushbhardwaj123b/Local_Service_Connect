// =====================================================================
// LOCAL SERVICE BOOKING SYSTEM - MODULE 3 + OVERALL COORDINATION
// Member      : Devyansh Bhardwaj
// Role        : Search + User Booking (and overall coordination)
// Contribution: Provider search (2-pass DMA), sorting, provider selection, Booking object creation, user active-booking stack, user booking menu; plus shared headers and main() that join all modules
// Depends on : Module 2 (searches the provider linked list), Module 1 (current_access_user), Module 4 (enqueues into provider waiting queue; cancel/rate/history from the booking menu)
//
// Is file mein sirf is member ka code hai (original single-file code se
// as-it-is nikala gaya, koi logic change nahi). Har block ke upar
// original file ke line numbers likhe hain.
// Poora program chalane ke liye original single .cpp use hota hai.
// =====================================================================

// ---------- Headers, namespace, MAX macro [Overall coordination]  (original lines 2-6) ----------
#include <iostream>
#include <string>
using namespace std;

#define max 5

// ---------- Global counter: next_booking_number  (original lines 10-10) ----------
int next_booking_number = 1000;

// ---------- Forward declarations (User, Provider) [Overall coordination]  (original lines 12-13) ----------
class User;
class Provider;

// ---------- class Booking  (original lines 15-35) ----------
// Every booking is created once. Stacks and queues store its address.
class Booking
{
public:
    int booking_number;
    User* user_reference;
    Provider* provider_reference;
    string service;
    string area;
    string status;

    Booking(int number, User* user, Provider* provider, string service_name, string area_name)
    {
        booking_number = number;
        user_reference = user;
        provider_reference = provider;
        service = service_name;
        area = area_name;
        status = "WAITING";
    }
};

// ---------- User active booking stack: push/pop/temp/remove  (original lines 710-771) ----------
// ------------------------- USER CLASS: STACK FUNCTIONS -------------------------
void User::push_user_booking_stack(Booking* value)
{
    if (user_booking_stack_top == max - 1)
        cout << "User booking stack is full.\n";
    else
    {
        user_booking_stack_top++;
        user_booking_stack[user_booking_stack_top] = value;
    }
}

void User::pop_user_booking_stack()
{
    if (user_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = user_booking_stack[user_booking_stack_top];
    user_booking_stack_top--;
}

void User::push_temp_booking_stack(Booking* value)
{
    if (temp_booking_stack_top < max - 1)
    {
        temp_booking_stack_top++;
        temp_booking_stack[temp_booking_stack_top] = value;
    }
}

void User::pop_temp_booking_stack()
{
    if (temp_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_booking_stack[temp_booking_stack_top];
    temp_booking_stack_top--;
}

void User::remove_user_booking_from_stack(Booking* target)
{
    temp_booking_stack_top = -1;

    while (user_booking_stack_top != -1)
    {
        pop_user_booking_stack();
        if (data_structure_value != target)
            push_temp_booking_stack(data_structure_value);
    }

    while (temp_booking_stack_top != -1)
    {
        pop_temp_booking_stack();
        push_user_booking_stack(data_structure_value);
    }
}

// ---------- display_user_booking_stack()  (original lines 904-920) ----------
void User::display_user_booking_stack()
{
    if (user_booking_stack_top == -1)
    {
        cout << "No active bookings.\n";
        return;
    }

    cout << "\n--- ACTIVE BOOKINGS (latest first) ---\n";
    int i;
    for (i = user_booking_stack_top; i >= 0; i--)
    {
        Booking* value = user_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | " << value->service
             << " | " << value->area << " | Status: " << value->status << "\n";
    }
}

// ---------- create_booking() - search, 2-pass DMA, bubble sort, booking object  (original lines 1285-1460) ----------
// ------------------------- SEARCH / SORT / CREATE BOOKING -------------------------
void create_booking()
{
    if (current_access_user->user_booking_stack_top == max - 1)
    {
        cout << "Your active booking stack is full (maximum 5).\n";
        return;
    }

    string service, area;
    int choice;

    cout << "\nChoose service:\n1. Plumber\n2. Carpenter\n3. Electrician\n4. Geyser Repair\n";
    cout << "5. AC Repair\n6. Painter\n7. Cleaner\n8. Appliance Repair\n9. Vegetable Vendor\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
        case 1: service = "Plumber"; break;
        case 2: service = "Carpenter"; break;
        case 3: service = "Electrician"; break;
        case 4: service = "Geyser Repair"; break;
        case 5: service = "AC Repair"; break;
        case 6: service = "Painter"; break;
        case 7: service = "Cleaner"; break;
        case 8: service = "Appliance Repair"; break;
        case 9: service = "Vegetable Vendor"; break;
        default:
            cout << "Invalid service choice. Booking cancelled.\n";
            return;
    }

    cout << "\nChoose area:\n1. Rishikesh\n2. Raipur\n3. Dehradun\n4. Clement Town\n5. Prem Nagar\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
        case 1: area = "Rishikesh"; break;
        case 2: area = "Raipur"; break;
        case 3: area = "Dehradun"; break;
        case 4: area = "Clement Town"; break;
        case 5: area = "Prem Nagar"; break;
        default:
            cout << "Invalid area choice. Booking cancelled.\n";
            return;
    }

    // Pass 1: count exact matches. A provider is shown only if waiting queue is not full.
    int count = 0;
    Provider* temp = provider_linked_list_head;
    while (temp != nullptr)
    {
        if (temp->service == service && temp->area == area &&
            temp->provider_waiting_queue_front != (temp->provider_waiting_queue_rear + 1) % max)
            count++;
        temp = temp->provider_next;
    }

    if (count == 0)
    {
        cout << "No available provider found for this service and area.\n";
        return;
    }

    // Pass 2: dynamically allocate only the number of matching Provider pointers.
    Provider** results = new Provider*[count];
    temp = provider_linked_list_head;
    int index = 0;
    while (temp != nullptr)
    {
        if (temp->service == service && temp->area == area &&
            temp->provider_waiting_queue_front != (temp->provider_waiting_queue_rear + 1) % max)
        {
            results[index] = temp;
            index++;
        }
        temp = temp->provider_next;
    }

    cout << "\nDisplay providers by:\n1. Current order\n2. Highest rating\n3. Highest completed work\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    int i, j;
    if (choice == 2)
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                double first_rating = 0, second_rating = 0;
                if (results[j]->total_ratings_received > 0)
                    first_rating = results[j]->total_rating / results[j]->total_ratings_received;
                if (results[j + 1]->total_ratings_received > 0)
                    second_rating = results[j + 1]->total_rating / results[j + 1]->total_ratings_received;

                if (first_rating < second_rating)
                {
                    Provider* swap_provider = results[j];
                    results[j] = results[j + 1];
                    results[j + 1] = swap_provider;
                }
            }
        }
    }
    else if (choice == 3)
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if (results[j]->work_count < results[j + 1]->work_count)
                {
                    Provider* swap_provider = results[j];
                    results[j] = results[j + 1];
                    results[j + 1] = swap_provider;
                }
            }
        }
    }
    else if (choice != 1)
    {
        cout << "Invalid choice. Current order will be used.\n";
    }

    cout << "\n--- AVAILABLE PROVIDERS ---\n";
    for (i = 0; i < count; i++)
    {
        double average_rating = 0;
        if (results[i]->total_ratings_received > 0)
            average_rating = results[i]->total_rating / results[i]->total_ratings_received;

        cout << i + 1 << ". " << results[i]->name << " | ID: " << results[i]->id
             << " | Service: " << results[i]->service << " | Area: " << results[i]->area
             << " | Rating: " << average_rating << "/5"
             << " | Completed work: " << results[i]->work_count << "\n";
    }

    cout << "0. Cancel\nChoose provider: ";
    cin >> choice;
    cin.ignore();
    if (choice == 0)
    {
        delete[] results;
        return;
    }
    if (choice < 1 || choice > count)
    {
        cout << "Invalid provider choice.\n";
        delete[] results;
        return;
    }

    Provider* selected_provider = results[choice - 1];
    delete[] results;

    // Check again before creating a booking.
    if (selected_provider->provider_waiting_queue_front ==
        (selected_provider->provider_waiting_queue_rear + 1) % max)
    {
        cout << "This provider's waiting queue is full.\n";
        return;
    }

    Booking* new_booking = new Booking(next_booking_number, current_access_user,
                                       selected_provider, service, area);
    next_booking_number++;
    selected_provider->enqueue_provider_waiting_queue(new_booking);
    current_access_user->push_user_booking_stack(new_booking);

    cout << "Booking created successfully. Booking number: " << new_booking->booking_number
         << " | Initial status: WAITING\n";
}

// ---------- user_booking_menu()  (original lines 1559-1584) ----------
// ------------------------- USER BOOKING MENU -------------------------
void user_booking_menu()
{
    int choice;
    while (1)
    {
        cout << "\n--- USER BOOKING MENU ---\n";
        cout << "1. Create booking\n2. Cancel booking\n3. Recent active bookings\n";
        cout << "4. Recent cancelled/rejected bookings\n5. Recent completed bookings\n";
        cout << "6. Rate a booking\n0. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1: create_booking(); break;
            case 2: cancel_booking(); break;
            case 3: current_access_user->display_user_booking_stack(); break;
            case 4: current_access_user->display_cancel_booking_stack(); break;
            case 5: current_access_user->display_completed_booking_stack(); break;
            case 6: rate_booking(); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

// ---------- main() - main menu [Overall coordination]  (original lines 1841-1878) ----------
// ------------------------- MAIN MENU -------------------------
int main()
{
    while (1)
    {
        int choice;
        cout << "\n========== LOCAL SERVICE BOOKING SYSTEM ==========\n";
        cout << "1. Sign up as User\n2. Sign up as Provider\n";
        cout << "3. Sign in as User\n4. Sign in as Provider\n0. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                sign_up_user();
                break;
            case 2:
                sign_up_provider();
                break;
            case 3:
                sign_in_user();
                if (current_access_user != nullptr)
                    user_dashboard();
                break;
            case 4:
                sign_in_provider();
                if (current_access_provider != nullptr)
                    provider_dashboard();
                break;
            case 0:
                cout << "Thank you for using Local Service Booking System.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
