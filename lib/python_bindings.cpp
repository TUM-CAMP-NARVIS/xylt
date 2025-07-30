#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "library.h"

namespace py = pybind11;

PYBIND11_MODULE(pyxylt, m) {
    m.doc() = "Python bindings for XY Lookup Table Library";

    py::class_<IntrinsicParameters>(m, "IntrinsicParameters")
        .def(py::init<>())
        .def(py::init < float, float, float, float, unsigned int, unsigned int, std::array < float, 6 >,
             std::array<float, 2> > ())
        .def(py::init<const IntrinsicParameters&>())
        .def_readwrite("fov_x", &IntrinsicParameters::fov_x)
        .def_readwrite("fov_y", &IntrinsicParameters::fov_y)
        .def_readwrite("c_x", &IntrinsicParameters::c_x)
        .def_readwrite("c_y", &IntrinsicParameters::c_y)
        .def_readwrite("width", &IntrinsicParameters::width)
        .def_readwrite("height", &IntrinsicParameters::height)
        .def_readwrite("radial_distortion", &IntrinsicParameters::radial_distortion)
        .def_readwrite("tangential_distortion", &IntrinsicParameters::tangential_distortion)
        .def_readwrite("metric_radius", &IntrinsicParameters::metric_radius)
        .def("__eq__", &IntrinsicParameters::operator==)
        .def("get_intrinsic_params", &IntrinsicParameters::getIntrinsicParams);

    py::class_<XYTableData, std::shared_ptr<XYTableData>>(m, "XYTableData")
        .def(py::init<>())
        .def_readwrite("width", &XYTableData::width)
        .def_readwrite("height", &XYTableData::height)
        .def_readwrite("data", &XYTableData::data);

    m.def("create_xy_lookup_table", &create_xy_lookup_table, "Create XY lookup table from camera parameters",
          py::arg("calib"), py::arg("xy_table"));
}
