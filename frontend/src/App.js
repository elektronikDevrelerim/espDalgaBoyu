import React, { useEffect, useRef, useState } from "react";
import Chart from "chart.js/auto";
import { CategoryScale } from "chart.js";

import { Line } from "react-chartjs-2";

import Paho from "paho-mqtt";

const App = () => {
  const ssl =
    window.location.protocol === "https:"
      ? (window.location.protocol = "http")
      : null;
  console.log(ssl);
  const chartRef = useRef(null);
  const client = new Paho.Client("broker.hivemq.com", Number(8000), "wss");
  client.onMessageArrived = onMessageArrived;
  client.onConnectionLost = onConnectionLost;
  client.connect({ onSuccess: onConnect });

  function onConnect() {
    console.log("onConnect");
    client.subscribe("dalgaBoyu_ESP8266");
  }

  Chart.register(CategoryScale);

  const [data, setData] = useState([
    { id: 1, nanometre: 10 },
    { id: 2, nanometre: 20 },
  ]);

  function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost:" + responseObject.errorMessage);
    }
  }

  function onMessageArrived(message) {
    if (message.topic === "dalgaBoyu_ESP8266") {
      var newData = {
        id: data.length + 1,
        nanometre: Number(message.payloadString),
      };
      setChartData((prevState) => {
        let updatedLabels = [...prevState.labels];
        let updatedData = [...prevState.datasets[0].data];

        if (updatedLabels.length >= 25) {
          updatedLabels = [1];
          updatedData = [newData.nanometre];
        } else {
          updatedLabels.push(updatedLabels.length + 1);
          updatedData.push(newData.nanometre);
        }
        return {
          ...prevState,
          labels: updatedLabels,
          datasets: [
            {
              ...prevState.datasets[0],
              data: updatedData,
            },
          ],
        };
      });
      // setChartData((prevState) => ({
      //   ...prevState,
      //   labels: [
      //     ...prevState.labels,
      //     prevState.labels.length >= 20 ? 1 : prevState.labels.length + 1,
      //   ],
      //   datasets: [
      //     {
      //       ...prevState.datasets[0],
      //       data: [...prevState.datasets[0].data, newData.nanometre],
      //     },
      //   ],
      // }));
    } else {
      console.log("onMessageArrived:" + message.payloadString);
    }
  }

  const [chartData, setChartData] = useState({
    labels: [],
    datasets: [
      {
        label: "Dalga Boyu",
        data: [],
        backgroundColor: ["lightgreen"],
        borderColor: "black",
        borderWidth: 2,
      },
    ],
  });

  return (
    <div className="flex flex-col justify-center items-center p-20">
      <h1 className="font-bold text-lg">Arduino İle Dalga Boyu Ölçümü</h1>
      <div className="">
        <Line
          data={chartData}
          width={1400}
          height={600}
          options={{
            responsive: true,
            plugins: {
              legend: {
                display: false,
                labels: {
                  color: "black",
                  font: {
                    family: "Montserrat",
                    size: 14,
                    weight: "bold",
                  },
                },
              },
            },
          }}
        />
        <h1 className="font-bold text-center">
          <br />
          <br />
          {chartData.datasets[0].data[
            chartData.datasets[0].data.length - 1
          ]?.toFixed(2)}{" "}
          nM
        </h1>
      </div>
    </div>
  );
};

export default App;
