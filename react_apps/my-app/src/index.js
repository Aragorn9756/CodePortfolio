import React from 'react';
import ReactDOM from 'react-dom';

class ReverseString extends React.Component {

    constructor(props) {
        super(props);

        this.state = {
            userInput: props.userInput,
            output: props.output = ''
        }
    }

    reverseInput (input) {
        //make sure input is string
        input = String(input);
        var output;
        for (var i = input.length - 1; i >= 0; i++) {
            output += input.charAt(i);
        }
        return output;
    }

    handleInputRecieved(event) {
        var uInput = this.state.userInput;
        uInput = event.target.value;

        var revOutput = this.state.output;
        revOutput = this.reverseInput(revOutput);

        this.setState({ userInput: uInput});
        this.setState({output: revOutput});
    }

    render() {
        return (
            <div>
                <label>
                  Enter Text:
                </label>
                <input type="text" value={this.state.userInput} onChange={this.handleInputRecieved.bind(this)}/>
                <br/>
                <p>
                    Your text reversed: {this.props.output}
                </p>
            </div>
        );
    }
}

class countString extends React.Component {

    constructor(props) {
        super(props);

        this.state = {
            userInput: props.userInput,
            inputLen: props.inputLen
        }
    }

    handleInputRecieved(event) {
        var userInput = this.state.userInput;
        userInput = event.target.value;

        var stringLen = this.state.stringLen;
        stringLen = userInput.length;

        this.setState({userInput: userInput});
        this.setState({stringLen: stringLen});
    }

    render() {
        return (
            <div>
                <label>
                  Enter Text:
                </label>
                <input type="text" value={this.state.userInput} onChange={this.handleInputRecieved.bind(this)}/>
                <br/>
                <p>
                    Number of Characters: {this.props.inputLen}
                </p>
            </div>
        );
    }
}

ReactDOM.render(ReverseString, document.getElementById('root'));
ReactDOM.render(countString, document.getElementById('root'));