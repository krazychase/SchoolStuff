# !/bin/bash/

while [[ true ]]; do

    echo "
    -=-=-=-=-= FIREWALL EDITOR =-=-=-=-=-
    1 - Add rule
    2 - Delete rule
    3 - Output Report
    0 - Quit
    h - Help
    "
    echo -n "Enter Option: "
    read option

    if [[ $option == "1" ]]; then
        
        echo "

        -=-=-= Add Rule =-=-=-
        INPUT
        FORWARD
        OUTPUT
        help
        "
        echo -n "Enter chain: "
        read chain

        if [[ ${chain^^} == "HELP" ]]; then
            echo "

            -= Help =-
            1 - INPUT - This chain is used to control the behavior for incoming connections. 
            2 - FORWARD - This chain is used for incoming connections that aren’t actually being delivered locally.
            3 - OUTPUT - This chain is used for outgoing connections.
            "
            echo -n "Enter chain: "
            read chain

        fi

        echo -n "

        -=-=-= Add Rule =-=-=-
        Enter IP Address:"
        read ipaddress
       
        echo "
        
        -=-=-= Add Rule =-=-=-
        ACCEPT
        DROP
        "
        echo -n "Enter what you want to do with  the connection: "
        read preference

        echo -n "
        
        $preference connections from $chain $ipaddress? [y/n]:
        "
        read confirmation
        if [[ ${confirmation^} == "Y" ]]; then
            iptables -A ${chain^^} -s ${ipaddress^^} -j ${preference^^}
            echo "Done . . . "
        fi

    elif [[ $option == "2" ]]; then

        echo "

        -=-=-= Delete Rule =-=-=-
        INPUT
        FORWARD
        OUTPUT
        help        
        "

        echo -n "Enter chain containing rule to delete: "
        read chain

        if [[ ${chain^^} == "HELP" ]]; then
            echo "

            -= Help =-
            1 - INPUT - This chain is used to control the behavior for incoming connections. 
            2 - FORWARD - This chain is used for incoming connections that aren’t actually being delivered locally.
            3 - OUTPUT - This chain is used for outgoing connections.
            "
            echo -n "Enter chain: "
            read chain
        fi

        iptables -L ${chain^^} --line-numbers

        echo -n "Enter rule number to delete: "
        read rule

        echo -n "
        
        Delete rule $rule from $chain? [y/n]:
        "
        read confirmation
        if [[ ${confirmation^} == "Y" ]]; then
            iptables -D ${chain^^} $rule
            echo "Done . . . "
        fi


    elif [[ $option == "3" ]]; then

        reportRaw="$(sudo iptables -L)"
        report=""
        while IFS= read -r line; do
            report="$report $line <br>"
        done <<< "$reportRaw"

        cat > report.html <<- _EOF_
<html>
    <head>
        <title>
            Iptables Report
        </title>
    </head>

    <body>
        <h1>Iptables Report</h1>
        <p><pre>$report<pre><p>
    </body>
</html>

_EOF_

        echo "Report outputted"

    elif [[ $option == "0" ]]; then
        echo "
        Goodbye . . . 
        "
        exit 0

    elif [[ ${option^} == "H" ]]; then

        echo "

        -=-=-= Help =-=-=-
        Iptables is used to set up, maintain, and inspect the tables of IP
        packet filter rules in the Linux kernel. Several different tables
        may be defined. Each table contains a number of built-in chains
        and may also contain user-defined chains.

        Each chain is a list of rules which can match a set of packets.
        Each rule specifies what to do with a packet that matches.
        This is called a 'target', which may be a jump to a 
        user-defined chain in the same table. 

        This tool aims to make the modification of these rules easier.
        Simply follow the onscreen prompts to add, delete, and view rules.
        "

    else
        echo "Command not recognized . . . "
    fi
    
    read -p "Enter to continue . . . "
done