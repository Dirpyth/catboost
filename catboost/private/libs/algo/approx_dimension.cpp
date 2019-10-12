#include "approx_dimension.h"

#include <catboost/private/libs/labels/label_converter.h>
#include <catboost/private/libs/options/catboost_options.h>
#include <catboost/private/libs/options/metric_options.h>


namespace NCB {

    ui32 GetApproxDimension(
        const NCatboostOptions::TCatBoostOptions& catBoostOptions,
        const TLabelConverter& labelConverter) {

        const ELossFunction lossFunction = catBoostOptions.LossFunctionDescription.Get().GetLossFunction();
        const bool isMulticlass = IsMultiClassOnly(lossFunction, catBoostOptions.MetricOptions);

        if (isMulticlass) {
            return (ui32)labelConverter.GetApproxDimension();
        }
        return ui32(1);
    }

}