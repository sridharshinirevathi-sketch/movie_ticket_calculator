let selectedMovie = "";


// ======================================
// Select Movie
// ======================================
function selectMovie(movie) {

    selectedMovie = movie;

    document.getElementById("movieName").value = movie;

    window.scrollTo({
        top: document.querySelector(".booking").offsetTop,
        behavior: "smooth"
    });
}


// ======================================
// Calculate Ticket
// ======================================
function calculateTicket() {

    // Check movie
    if (selectedMovie === "") {

        alert("Please select a movie first!");

        return;
    }


    // Get username
    const username =
        document.getElementById("username").value.trim();


    // Get email
    const emailId =
        document.getElementById("emailId").value.trim();


    // Check username
    if (username === "") {

        alert("Please enter username!");

        return;
    }


    // Check email
    if (emailId === "") {

        alert("Please enter email ID!");

        return;
    }


    // Adult tickets
    const adultTickets =
        parseInt(
            document.getElementById("adultTickets").value
        ) || 0;


    // Child tickets
    const childTickets =
        parseInt(
            document.getElementById("childTickets").value
        ) || 0;


    // Show time
    const showTime =
        document.getElementById("showTime").value;


    // Snacks
    const snackSelect =
        document.getElementById("snacks");


    const snackPrice =
        parseInt(snackSelect.value) || 0;


    const snackName =
        snackSelect.options[
            snackSelect.selectedIndex
        ].text;


    // ======================================
    // Calculate Amount
    // ======================================

    const adultAmount =
        adultTickets * 200;


    const childAmount =
        childTickets * 120;


    const ticketAmount =
        adultAmount + childAmount;


    const subtotal =
        ticketAmount + snackPrice;


    // Discount
    let discount = 0;


    if (subtotal >= 1000) {

        discount = 100;

    }
    else if (subtotal >= 500) {

        discount = 50;
    }


    // Amount after discount
    const amountAfterDiscount =
        subtotal - discount;


    // GST
    const gst =
        amountAfterDiscount * 0.05;


    // Final amount
    const finalAmount =
        amountAfterDiscount + gst;


    // ======================================
    // Booking Summary
    // ======================================

    document.getElementById("summary").innerHTML = `

        <p>
            <b>Username:</b>
            ${username}
        </p>

        <p>
            <b>Email ID:</b>
            ${emailId}
        </p>

        <p>
            <b>Movie:</b>
            ${selectedMovie}
        </p>

        <p>
            <b>Show Time:</b>
            ${showTime}
        </p>

        <p>
            <b>Adult Tickets:</b>
            ${adultTickets}
        </p>

        <p>
            <b>Child Tickets:</b>
            ${childTickets}
        </p>

        <p>
            <b>Ticket Amount:</b>
            ₹${ticketAmount}
        </p>

        <p>
            <b>Snacks:</b>
            ${snackName}
        </p>

        <p>
            <b>Snacks Amount:</b>
            ₹${snackPrice}
        </p>

        <p>
            <b>Subtotal:</b>
            ₹${subtotal}
        </p>

        <p>
            <b>Discount:</b>
            ₹${discount}
        </p>

        <p>
            <b>GST (5%):</b>
            ₹${gst.toFixed(2)}
        </p>

        <hr>

        <p>
            <b>Final Amount:</b>
            ₹${finalAmount.toFixed(2)}
        </p>

        <p id="bookingStatus">
            Saving booking...
        </p>
    `;


    // ======================================
    // Send Data to Flask
    // ======================================

    fetch("/book", {

        method: "POST",

        headers: {
            "Content-Type": "application/json"
        },

        body: JSON.stringify({

            username: username,

            email_id: emailId,

            movie_name: selectedMovie,

            show_time: showTime,

            adults: adultTickets,

            children: childTickets,

            snack_name: snackName,

            snack_amount: snackPrice,

            ticket_amount: ticketAmount,

            subtotal: subtotal,

            discount: discount,

            gst: gst,

            total_amount: finalAmount

        })

    })

    .then(response => response.json())

    .then(data => {

        if (data.success) {

            document.getElementById(
                "bookingStatus"
            ).innerHTML = `

                <h3>
                    🎉 Booking Successful!
                </h3>

            `;

        }
        else {

            document.getElementById(
                "bookingStatus"
            ).innerHTML = `

                <p style="color:red;">
                    Booking failed:
                    ${data.message}
                </p>

            `;
        }

    })

    .catch(error => {

        console.error(error);

        document.getElementById(
            "bookingStatus"
        ).innerHTML = `

            <p style="color:red;">
                Unable to connect to server.
            </p>

        `;

    });


    // Scroll to result
    document.getElementById(
        "result"
    ).scrollIntoView({

        behavior: "smooth"

    });
}