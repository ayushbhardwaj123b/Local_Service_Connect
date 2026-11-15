// =====================================================================
// LOCAL SERVICE BOOKING SYSTEM - MODULE 4
// Member      : Ashutosh Negi
// Role        : Requests + Completion (Overall Project Leader)
// Contribution: Provider circular queues (waiting/main/accepted), request processing, cancellation, completion, rating, cancelled/completed stacks
// Depends on : Module 3 (Booking objects and user active stack), Module 1 + 2 (User / Provider classes and current_access_provider)
//
// Is file mein sirf is member ka code hai (original single-file code se
// as-it-is nikala gaya, koi logic change nahi). Har block ke upar
// original file ke line numbers likhe hain.
// Poora program chalane ke liye original single .cpp use hota hai.
// =====================================================================

// ---------- Global: data_structure_value (pop/dequeue carrier)  (original lines 231-233) ----------
// pop() and dequeue() are void functions. This pointer carries the removed Booking
// to the next operation, keeping the data-structure functions simple.
Booking* data_structure_value = nullptr;

// ---------- User cancelled/rejected stack: push/pop/temp  (original lines 773-828) ----------
void User::push_temp_cancel_booking_stack(Booking* value)
{
    if (temp_cancel_booking_stack_top < max - 1)
    {
        temp_cancel_booking_stack_top++;
        temp_cancel_booking_stack[temp_cancel_booking_stack_top] = value;
    }
}

void User::pop_temp_cancel_booking_stack()
{
    if (temp_cancel_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_cancel_booking_stack[temp_cancel_booking_stack_top];
    temp_cancel_booking_stack_top--;
}

void User::pop_cancel_booking_stack()
{
    if (cancel_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = cancel_booking_stack[cancel_booking_stack_top];
    cancel_booking_stack_top--;
}

void User::push_cancel_booking_stack(Booking* value)
{
    // If full, drop the oldest booking and preserve the newest four.
    if (cancel_booking_stack_top == max - 1)
    {
        temp_cancel_booking_stack_top = -1;
        while (cancel_booking_stack_top > 0)
        {
            pop_cancel_booking_stack();
            push_temp_cancel_booking_stack(data_structure_value);
        }

        cancel_booking_stack_top = -1;
        while (temp_cancel_booking_stack_top != -1)
        {
            pop_temp_cancel_booking_stack();
            push_cancel_booking_stack(data_structure_value);
        }
    }

    cancel_booking_stack_top++;
    cancel_booking_stack[cancel_booking_stack_top] = value;
}

// ---------- User completed stack: push/pop/temp/remove (rating ke liye)  (original lines 830-902) ----------
void User::push_temp_completed_booking_stack(Booking* value)
{
    if (temp_completed_booking_stack_top < max - 1)
    {
        temp_completed_booking_stack_top++;
        temp_completed_booking_stack[temp_completed_booking_stack_top] = value;
    }
}

void User::pop_temp_completed_booking_stack()
{
    if (temp_completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_completed_booking_stack[temp_completed_booking_stack_top];
    temp_completed_booking_stack_top--;
}

void User::pop_completed_booking_stack()
{
    if (completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = completed_booking_stack[completed_booking_stack_top];
    completed_booking_stack_top--;
}

void User::push_completed_booking_stack(Booking* value)
{
    if (completed_booking_stack_top == max - 1)
    {
        temp_completed_booking_stack_top = -1;
        while (completed_booking_stack_top > 0)
        {
            pop_completed_booking_stack();
            push_temp_completed_booking_stack(data_structure_value);
        }

        completed_booking_stack_top = -1;
        while (temp_completed_booking_stack_top != -1)
        {
            pop_temp_completed_booking_stack();
            push_completed_booking_stack(data_structure_value);
        }
    }

    completed_booking_stack_top++;
    completed_booking_stack[completed_booking_stack_top] = value;
}

void User::remove_user_completed_booking_stack(Booking* target)
{
    temp_completed_booking_stack_top = -1;

    while (completed_booking_stack_top != -1)
    {
        pop_completed_booking_stack();
        if (data_structure_value != target)
            push_temp_completed_booking_stack(data_structure_value);
    }

    while (temp_completed_booking_stack_top != -1)
    {
        pop_temp_completed_booking_stack();
        push_completed_booking_stack(data_structure_value);
    }
}

// ---------- display_cancel_booking_stack()  (original lines 922-938) ----------
void User::display_cancel_booking_stack()
{
    if (cancel_booking_stack_top == -1)
    {
        cout << "No cancelled/rejected bookings.\n";
        return;
    }

    cout << "\n--- RECENT CANCELLED / REJECTED BOOKINGS ---\n";
    int i;
    for (i = cancel_booking_stack_top; i >= 0; i--)
    {
        Booking* value = cancel_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | " << value->service
             << " | Status: " << value->status << "\n";
    }
}

// ---------- display_completed_booking_stack()  (original lines 940-956) ----------
void User::display_completed_booking_stack()
{
    if (completed_booking_stack_top == -1)
    {
        cout << "No completed bookings waiting for rating.\n";
        return;
    }

    cout << "\n--- COMPLETED BOOKINGS WAITING FOR RATING ---\n";
    int i;
    for (i = completed_booking_stack_top; i >= 0; i--)
    {
        Booking* value = completed_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | " << value->service
             << " | Provider: " << value->provider_reference->name << "\n";
    }
}

// ---------- Provider waiting / main / accepted circular queues (+ temp queues)  (original lines 958-1283) ----------
// ------------------------- PROVIDER CLASS: QUEUE FUNCTIONS -------------------------
void Provider::enqueue_provider_waiting_queue(Booking* value)
{
    if (provider_waiting_queue_front == (provider_waiting_queue_rear + 1) % max)
        cout << "Provider waiting queue is full.\n";
    else if (provider_waiting_queue_front == -1 && provider_waiting_queue_rear == -1)
    {
        provider_waiting_queue_front = 0;
        provider_waiting_queue_rear = 0;
        provider_waiting_queue[0] = value;
    }
    else
    {
        provider_waiting_queue_rear = (provider_waiting_queue_rear + 1) % max;
        provider_waiting_queue[provider_waiting_queue_rear] = value;
    }
}

void Provider::dequeue_provider_waiting_queue()
{
    if (provider_waiting_queue_front == -1 && provider_waiting_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = provider_waiting_queue[provider_waiting_queue_front];
    if (provider_waiting_queue_front == provider_waiting_queue_rear)
        provider_waiting_queue_front = provider_waiting_queue_rear = -1;
    else
        provider_waiting_queue_front = (provider_waiting_queue_front + 1) % max;
}

void Provider::enqueue_temp_waiting_queue(Booking* value)
{
    if (temp_waiting_queue_front == (temp_waiting_queue_rear + 1) % max)
        cout << "Temporary waiting queue is full.\n";
    else if (temp_waiting_queue_front == -1 && temp_waiting_queue_rear == -1)
    {
        temp_waiting_queue_front = 0;
        temp_waiting_queue_rear = 0;
        temp_waiting_queue[0] = value;
    }
    else
    {
        temp_waiting_queue_rear = (temp_waiting_queue_rear + 1) % max;
        temp_waiting_queue[temp_waiting_queue_rear] = value;
    }
}

void Provider::dequeue_temp_waiting_queue()
{
    if (temp_waiting_queue_front == -1 && temp_waiting_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_waiting_queue[temp_waiting_queue_front];
    if (temp_waiting_queue_front == temp_waiting_queue_rear)
        temp_waiting_queue_front = temp_waiting_queue_rear = -1;
    else
        temp_waiting_queue_front = (temp_waiting_queue_front + 1) % max;
}

void Provider::remove_from_provider_waiting_queue(Booking* target)
{
    temp_waiting_queue_front = temp_waiting_queue_rear = -1;

    while (provider_waiting_queue_front != -1)
    {
        dequeue_provider_waiting_queue();
        if (data_structure_value != target)
            enqueue_temp_waiting_queue(data_structure_value);
    }

    while (temp_waiting_queue_front != -1)
    {
        dequeue_temp_waiting_queue();
        enqueue_provider_waiting_queue(data_structure_value);
    }
}

void Provider::display_provider_waiting_queue()
{
    if (provider_waiting_queue_front == -1)
    {
        cout << "Waiting queue has no requests.\n";
        return;
    }

    cout << "\n--- WAITING REQUESTS (front first) ---\n";
    int i = provider_waiting_queue_front;
    while (1)
    {
        Booking* value = provider_waiting_queue[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Phone: " << value->user_reference->phone << " | Service: " << value->service
             << " | Status: " << value->status << "\n";
        if (i == provider_waiting_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

void Provider::enqueue_provider_main_queue(Booking* value)
{
    if (provider_main_queue_front == (provider_main_queue_rear + 1) % max)
        cout << "Provider main queue is full.\n";
    else if (provider_main_queue_front == -1 && provider_main_queue_rear == -1)
    {
        provider_main_queue_front = provider_main_queue_rear = 0;
        provider_main_queue[0] = value;
    }
    else
    {
        provider_main_queue_rear = (provider_main_queue_rear + 1) % max;
        provider_main_queue[provider_main_queue_rear] = value;
    }
}

void Provider::dequeue_provider_main_queue()
{
    if (provider_main_queue_front == -1 && provider_main_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = provider_main_queue[provider_main_queue_front];
    if (provider_main_queue_front == provider_main_queue_rear)
        provider_main_queue_front = provider_main_queue_rear = -1;
    else
        provider_main_queue_front = (provider_main_queue_front + 1) % max;
}

void Provider::enqueue_temp_main_queue(Booking* value)
{
    if (temp_main_queue_front == (temp_main_queue_rear + 1) % max)
        cout << "Temporary main queue is full.\n";
    else if (temp_main_queue_front == -1 && temp_main_queue_rear == -1)
    {
        temp_main_queue_front = temp_main_queue_rear = 0;
        temp_main_queue[0] = value;
    }
    else
    {
        temp_main_queue_rear = (temp_main_queue_rear + 1) % max;
        temp_main_queue[temp_main_queue_rear] = value;
    }
}

void Provider::dequeue_temp_main_queue()
{
    if (temp_main_queue_front == -1 && temp_main_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_main_queue[temp_main_queue_front];
    if (temp_main_queue_front == temp_main_queue_rear)
        temp_main_queue_front = temp_main_queue_rear = -1;
    else
        temp_main_queue_front = (temp_main_queue_front + 1) % max;
}

void Provider::remove_from_provider_main_queue(Booking* target)
{
    temp_main_queue_front = temp_main_queue_rear = -1;

    while (provider_main_queue_front != -1)
    {
        dequeue_provider_main_queue();
        if (data_structure_value != target)
            enqueue_temp_main_queue(data_structure_value);
    }

    while (temp_main_queue_front != -1)
    {
        dequeue_temp_main_queue();
        enqueue_provider_main_queue(data_structure_value);
    }
}

void Provider::display_provider_main_queue()
{
    if (provider_main_queue_front == -1)
    {
        cout << "Main queue has no accepted bookings.\n";
        return;
    }

    cout << "\n--- ACCEPTED BOOKINGS (front first) ---\n";
    int i = provider_main_queue_front;
    while (1)
    {
        Booking* value = provider_main_queue[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Phone: " << value->user_reference->phone << " | Service: " << value->service
             << " | Status: " << value->status << "\n";
        if (i == provider_main_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

void Provider::enqueue_accepted_booking_queue(Booking* value)
{
    if (accepted_booking_queue_front == (accepted_booking_queue_rear + 1) % max)
        cout << "Accepted booking queue is full.\n";
    else if (accepted_booking_queue_front == -1 && accepted_booking_queue_rear == -1)
    {
        accepted_booking_queue_front = accepted_booking_queue_rear = 0;
        accepted_booking_queue[0] = value;
    }
    else
    {
        accepted_booking_queue_rear = (accepted_booking_queue_rear + 1) % max;
        accepted_booking_queue[accepted_booking_queue_rear] = value;
    }
}

void Provider::dequeue_accepted_booking_queue()
{
    if (accepted_booking_queue_front == -1 && accepted_booking_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = accepted_booking_queue[accepted_booking_queue_front];
    if (accepted_booking_queue_front == accepted_booking_queue_rear)
        accepted_booking_queue_front = accepted_booking_queue_rear = -1;
    else
        accepted_booking_queue_front = (accepted_booking_queue_front + 1) % max;
}

void Provider::enqueue_temp_accepted_booking_queue(Booking* value)
{
    if (temp_accepted_booking_queue_front == (temp_accepted_booking_queue_rear + 1) % max)
        cout << "Temporary accepted queue is full.\n";
    else if (temp_accepted_booking_queue_front == -1 && temp_accepted_booking_queue_rear == -1)
    {
        temp_accepted_booking_queue_front = temp_accepted_booking_queue_rear = 0;
        temp_accepted_booking_queue[0] = value;
    }
    else
    {
        temp_accepted_booking_queue_rear = (temp_accepted_booking_queue_rear + 1) % max;
        temp_accepted_booking_queue[temp_accepted_booking_queue_rear] = value;
    }
}

void Provider::dequeue_temp_accepted_booking_queue()
{
    if (temp_accepted_booking_queue_front == -1 && temp_accepted_booking_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_accepted_booking_queue[temp_accepted_booking_queue_front];
    if (temp_accepted_booking_queue_front == temp_accepted_booking_queue_rear)
        temp_accepted_booking_queue_front = temp_accepted_booking_queue_rear = -1;
    else
        temp_accepted_booking_queue_front = (temp_accepted_booking_queue_front + 1) % max;
}

void Provider::prepare_accepted_booking_queue()
{
    accepted_booking_queue_front = accepted_booking_queue_rear = -1;

    if (provider_main_queue_front == -1)
        return;

    int i = provider_main_queue_front;
    while (1)
    {
        Booking* value = provider_main_queue[i];
        if (value->status == "ACCEPTED")
            enqueue_accepted_booking_queue(value);
        if (i == provider_main_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

void Provider::remove_from_accepted_booking_queue(Booking* target)
{
    temp_accepted_booking_queue_front = temp_accepted_booking_queue_rear = -1;

    while (accepted_booking_queue_front != -1)
    {
        dequeue_accepted_booking_queue();
        if (data_structure_value != target)
            enqueue_temp_accepted_booking_queue(data_structure_value);
    }

    while (temp_accepted_booking_queue_front != -1)
    {
        dequeue_temp_accepted_booking_queue();
        enqueue_accepted_booking_queue(data_structure_value);
    }
}

void Provider::display_accepted_booking_queue()
{
    if (accepted_booking_queue_front == -1)
    {
        cout << "No accepted booking is available to complete.\n";
        return;
    }

    cout << "\n--- ACCEPTED BOOKINGS TO COMPLETE ---\n";
    int i = accepted_booking_queue_front;
    while (1)
    {
        Booking* value = accepted_booking_queue[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Service: " << value->service << " | Status: " << value->status << "\n";
        if (i == accepted_booking_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

// ---------- cancel_booking()  (original lines 1462-1508) ----------
// ------------------------- CANCEL BOOKING -------------------------
void cancel_booking()
{
    current_access_user->display_user_booking_stack();
    if (current_access_user->user_booking_stack_top == -1)
        return;

    int number;
    cout << "Enter booking number to cancel (0 to go back): ";
    cin >> number;
    cin.ignore();
    if (number == 0)
        return;

    Booking* target = nullptr;
    int i;
    for (i = current_access_user->user_booking_stack_top; i >= 0; i--)
    {
        if (current_access_user->user_booking_stack[i]->booking_number == number)
            target = current_access_user->user_booking_stack[i];
    }

    if (target == nullptr)
    {
        cout << "That booking is not in your active booking stack.\n";
        return;
    }

    if (target->status != "WAITING" && target->status != "ACCEPTED")
    {
        cout << "This booking cannot be cancelled in its current status.\n";
        return;
    }

    if (target->status == "WAITING")
        target->provider_reference->remove_from_provider_waiting_queue(target);
    else
    {
        target->provider_reference->remove_from_provider_main_queue(target);
        target->provider_reference->remove_from_accepted_booking_queue(target);
    }

    current_access_user->remove_user_booking_from_stack(target);
    target->status = "CANCELLED";
    current_access_user->push_cancel_booking_stack(target);
    cout << "Booking cancelled and moved to cancelled history.\n";
}

// ---------- rate_booking()  (original lines 1510-1557) ----------
// ------------------------- RATE BOOKING -------------------------
void rate_booking()
{
    current_access_user->display_completed_booking_stack();
    if (current_access_user->completed_booking_stack_top == -1)
        return;

    int number;
    cout << "Enter completed booking number to rate (0 to go back): ";
    cin >> number;
    cin.ignore();
    if (number == 0)
        return;

    Booking* target = nullptr;
    int i;
    for (i = current_access_user->completed_booking_stack_top; i >= 0; i--)
    {
        if (current_access_user->completed_booking_stack[i]->booking_number == number)
            target = current_access_user->completed_booking_stack[i];
    }

    if (target == nullptr)
    {
        cout << "Booking not found in your completed booking stack.\n";
        return;
    }

    int rating;
    cout << "Give rating from 1 to 5: ";
    cin >> rating;
    cin.ignore();
    if (rating < 1 || rating > 5)
    {
        cout << "Rating must be between 1 and 5.\n";
        return;
    }

    target->provider_reference->total_rating += rating;
    target->provider_reference->total_ratings_received++;

    double average_rating = target->provider_reference->total_rating /
                            target->provider_reference->total_ratings_received;
    cout << "Rating saved. Provider's average rating is now " << average_rating << "/5.\n";

    // Remove rated booking so it cannot be rated twice.
    current_access_user->remove_user_completed_booking_stack(target);
}

// ---------- Provider recent completed stack  (original lines 1586-1660) ----------
// ------------------------- PROVIDER CLASS: RECENT COMPLETED STACK -------------------------
void Provider::push_temp_recent_completed_booking_stack(Booking* value)
{
    if (temp_recent_completed_booking_stack_top < max - 1)
    {
        temp_recent_completed_booking_stack_top++;
        temp_recent_completed_booking_stack[temp_recent_completed_booking_stack_top] = value;
    }
}

void Provider::pop_temp_recent_completed_booking_stack()
{
    if (temp_recent_completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_recent_completed_booking_stack[temp_recent_completed_booking_stack_top];
    temp_recent_completed_booking_stack_top--;
}

void Provider::pop_recent_completed_booking_stack()
{
    if (recent_completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = recent_completed_booking_stack[recent_completed_booking_stack_top];
    recent_completed_booking_stack_top--;
}

void Provider::push_recent_completed_booking_stack(Booking* value)
{
    if (recent_completed_booking_stack_top == max - 1)
    {
        temp_recent_completed_booking_stack_top = -1;
        while (recent_completed_booking_stack_top > 0)
        {
            pop_recent_completed_booking_stack();
            push_temp_recent_completed_booking_stack(data_structure_value);
        }

        recent_completed_booking_stack_top = -1;
        while (temp_recent_completed_booking_stack_top != -1)
        {
            pop_temp_recent_completed_booking_stack();
            recent_completed_booking_stack_top++;
            recent_completed_booking_stack[recent_completed_booking_stack_top] = data_structure_value;
        }
    }

    recent_completed_booking_stack_top++;
    recent_completed_booking_stack[recent_completed_booking_stack_top] = value;
}

void Provider::display_recent_completed_booking_stack()
{
    if (recent_completed_booking_stack_top == -1)
    {
        cout << "No completed bookings yet.\n";
        return;
    }

    cout << "\n--- RECENT COMPLETED BOOKINGS ---\n";
    int i;
    for (i = recent_completed_booking_stack_top; i >= 0; i--)
    {
        Booking* value = recent_completed_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Service: " << value->service << "\n";
    }
}

// ---------- process_booking() - accept / reject / keep waiting  (original lines 1662-1723) ----------
// ------------------------- PROCESS PROVIDER REQUEST -------------------------
void process_booking()
{
    if (current_access_provider->provider_waiting_queue_front == -1)
    {
        cout << "No waiting requests to process.\n";
        return;
    }

    Booking* first_booking = current_access_provider->provider_waiting_queue[
        current_access_provider->provider_waiting_queue_front];
    cout << "\n--- FIRST WAITING REQUEST ---\n";
    cout << "Booking number: " << first_booking->booking_number << "\n";
    cout << "User: " << first_booking->user_reference->name << "\n";
    cout << "Phone: " << first_booking->user_reference->phone << "\n";
    cout << "Email: " << first_booking->user_reference->email << "\n";
    cout << "Service: " << first_booking->service << "\nArea: " << first_booking->area << "\n";
    cout << "Status: " << first_booking->status << "\n";

    int choice;
    cout << "1. Accept\n2. Reject\n3. Keep waiting\n0. Back\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 0)
        return;

    if (choice == 1)
    {
        if (current_access_provider->provider_main_queue_front ==
            (current_access_provider->provider_main_queue_rear + 1) % max)
        {
            cout << "Main queue is full. Cannot accept this booking right now.\n";
            return;
        }

        current_access_provider->dequeue_provider_waiting_queue();
        Booking* value = data_structure_value;
        value->status = "ACCEPTED";
        current_access_provider->enqueue_provider_main_queue(value);
        cout << "Booking accepted and moved to the main queue.\n";
    }
    else if (choice == 2)
    {
        current_access_provider->dequeue_provider_waiting_queue();
        Booking* value = data_structure_value;
        value->status = "REJECTED";

        value->user_reference->remove_user_booking_from_stack(value);
        value->user_reference->push_cancel_booking_stack(value);
        cout << "Booking rejected and moved to user's cancelled/rejected history.\n";
    }
    else if (choice == 3)
    {
        // Keep status WAITING; move the front request to the back.
        current_access_provider->dequeue_provider_waiting_queue();
        Booking* value = data_structure_value;
        current_access_provider->enqueue_provider_waiting_queue(value);
        cout << "Booking remains waiting and has moved to the back.\n";
    }
    else
        cout << "Invalid choice.\n";
}

// ---------- complete_booking() + provider_request_menu()  (original lines 1725-1796) ----------
// ------------------------- COMPLETE BOOKING -------------------------
void complete_booking()
{
    current_access_provider->display_provider_main_queue();
    if (current_access_provider->provider_main_queue_front == -1)
        return;

    current_access_provider->prepare_accepted_booking_queue();
    current_access_provider->display_accepted_booking_queue();
    if (current_access_provider->accepted_booking_queue_front == -1)
        return;

    int number;
    cout << "Enter accepted booking number to mark complete (0 to go back): ";
    cin >> number;
    cin.ignore();
    if (number == 0)
        return;

    Booking* target = nullptr;
    int i = current_access_provider->accepted_booking_queue_front;
    while (1)
    {
        if (current_access_provider->accepted_booking_queue[i]->booking_number == number)
            target = current_access_provider->accepted_booking_queue[i];
        if (i == current_access_provider->accepted_booking_queue_rear)
            break;
        i = (i + 1) % max;
    }

    if (target == nullptr)
    {
        cout << "Accepted booking not found.\n";
        return;
    }

    current_access_provider->remove_from_accepted_booking_queue(target);
    current_access_provider->remove_from_provider_main_queue(target);
    target->status = "COMPLETED";
    current_access_provider->work_count++;
    current_access_provider->push_recent_completed_booking_stack(target);

    target->user_reference->remove_user_booking_from_stack(target);
    target->user_reference->push_completed_booking_stack(target);

    cout << "Booking marked COMPLETED. Work count updated.\n";
}

void provider_request_menu()
{
    int choice;
    while (1)
    {
        cout << "\n--- PROVIDER REQUEST MENU ---\n";
        cout << "1. Process first waiting request\n2. View all accepted bookings (main queue)\n";
        cout << "3. View all waiting requests\n4. Mark accepted booking complete\n";
        cout << "5. Recent completed bookings\n0. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1: process_booking(); break;
            case 2: current_access_provider->display_provider_main_queue(); break;
            case 3: current_access_provider->display_provider_waiting_queue(); break;
            case 4: complete_booking(); break;
            case 5: current_access_provider->display_recent_completed_booking_stack(); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}
